#include "Game.h"
#include "Chess.h"
#include "Map.h"

using namespace std;

COORD ComXY(SHORT x, SHORT y)
{
	return COORD{ x, y };
}

Game::Game()
{
	WhosTurn = false;  //�մѥ���	
	cursorPos = ComXY(0, 7);
	chessPos = ComXY(0, 0); 
	int deadB = 0;
	int deadW = 0;
}

void Game::Interface() //�}�l����
{
	while (true)
	{
		switch (gui.mainMenu()) {
		case 1:
			AI = false;
			start(); //�}�l�C��
			break;
		case 2:
			gui.displayAboutScreen(); //�������
			break;
		case 3:
			exitGame(); //���}�C��
			break;
		case 4:
			AI = true;
			start(); //�}�l�C��
			break;
		default:
			break;
		}
	}
}

void Game::start()
{
	system("cls");      //�M���}�l�����e��

	gui.setVisible(true);                           //��ܴ��
	gui.dwSize(15);									//�]�w��Фj�p
	gui.displayGameScreen(GameMap, WhosTurn);		//��ܹC���e��

	playerControl();    //�i�J���a����
	reset();			//�C�������᭫�m
}

void Game::reset()  //���]�ѽL�B�^�X�ơB�_���Ѥl
{
	GameMap.reset();
	WhosTurn = false;
	cursorPos = ComXY(0, 7);
	chessPos = ComXY(0, 0);
	int deadB = 0;
	int deadW = 0;
}

void Game::exitGame() //���}�C��
{
	system("cls");
	gui.displayExitScreen();
	Sleep(200);//Delay 200ms
	exit(EXIT_SUCCESS);
}

void Game::playerControl() //��Ѷ��q
{
	bool oriTurn = false;
	bool isCatchChess = false;
	gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 2, CHESS_BOARD_Y + cursorPos.Y);
	gui.displayGameScreen(GameMap, WhosTurn);
	
	while (true)  //����L���� cursorPos �ӧ��� GameMap
	{
		if (AI == true && WhosTurn == true) 
		{
			// �o�̼gAI
			if (gui.MenuInGame()) 
			{
				// �^�X�����A���� ��ܵe��
				WhosTurn = !WhosTurn;
				gui.displayChessboard(GameMap);
				gui.displayGameInfo(WhosTurn, GameMap);
			}
		}
		else 
		{
			CHAR InputKB = _getch();
			switch (InputKB)
			{
			case KB_UP:
				if (cursorPos.Y > 0)
					--cursorPos.Y;
				break;
			case KB_DOWN:
				if (cursorPos.Y < 7)
					++cursorPos.Y;
				break;
			case KB_LEFT:
				if (cursorPos.X > 0)
					--cursorPos.X;
				break;
			case KB_RIGHT:
				if (cursorPos.X < 7)
					++cursorPos.X;
				break;
			case KB_ENTER:
				oriTurn = WhosTurn;
				if (!isCatchChess)
				{
					if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL && GameMap.pChess[cursorPos.X][cursorPos.Y]->getColor() == WhosTurn) //��Ѷ��q���P��Ѥl�W
					{
						gui.displayGameInfo(WhosTurn, GameMap, GameMap.pChess[cursorPos.X][cursorPos.Y]);
						gui.displayPossiblePath(GameMap.pChess[cursorPos.X][cursorPos.Y], GameMap); //��ܥi�H������m

						gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 2, CHESS_BOARD_Y + cursorPos.Y);
						chessPos = cursorPos;
						isCatchChess = true;
					}
				}
				else if (moveChess()) //���ʦ��\	
				{
					gui.displayChessboard(GameMap);
					gui.displayGameInfo(WhosTurn, GameMap);
					isCatchChess = false;
					if (oriTurn == WhosTurn) { continue; } //��ܥt�@�ӴѤl�A�^���ѼҦ��ê����i�Jcase Enter

					for (SHORT i = 0; i < ROW_SIZE; i++)
					{
						for (SHORT j = 0; j < COLUMN_SIZE; j++)
						{
							if (GameMap.pChess[i][j] != NULL &&
								GameMap.pChess[i][j]->getColor() == WhosTurn &&
								GameMap.pChess[i][j]->getMoved())
							{
								GameMap.pChess[i][j]->Moved();
							}
						}
					}

					if (!GameMap.get_King(true)->getAlive()) { Sleep(1000); gui.showAlert("       �դ�ӧQ       ", 5000); return; }
					if (!GameMap.get_King(false)->getAlive()) { Sleep(1000); gui.showAlert("       �¤�ӧQ       ", 5000); return; }
				}
				break;
			case KB_ESC: //�I�s���
				switch (gui.MenuInGame()) {
				case 1: //resume
					break;
				case 2: //restart
					if (gui.showConfirm("    �T�w���s�}�l ?    ")) { //22 chars
						reset();
						gui.displayGameScreen(GameMap, WhosTurn);
					}
					break;
				case 3: //back to main menu
					if (gui.showConfirm("  �T�w���ثe�ԧ� ?  "))
						return;
					break;
				case 4: //exit
					if (gui.showConfirm("      �T�w���} ?      "))
						exitGame();
				default:
					break;
				}
				break;
			default:
				break;
			}
			gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 2, CHESS_BOARD_Y + cursorPos.Y); //���ܴ�Ц�m
			gui.setVisible(true);			
		}		
	}
}

bool Game::moveChess() //�T�w����
{
	if (GameMap.pChess[chessPos.X][chessPos.Y]->isValid(cursorPos, GameMap)) //���ʪ��p
	{
		if (GameMap.pChess[chessPos.X][chessPos.Y]->isPassing(cursorPos.X, GameMap))
		{
			if (WhosTurn) 
			{
				gui.displayWDeathScreen(GameMap.pChess[cursorPos.X][chessPos.Y], deadW++);
			}			
			else
			{
				gui.displayBDeathScreen(GameMap.pChess[cursorPos.X][chessPos.Y], deadB++);
			}			
			GameMap.pChess[cursorPos.X][chessPos.Y]->setAlive(false);
			GameMap.pChess[cursorPos.X][chessPos.Y] = NULL;
		}
		if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL) //�Y�l���p	
		{
			if (WhosTurn) 
			{
				gui.displayWDeathScreen(GameMap.pChess[cursorPos.X][cursorPos.Y], deadW++);
			}			
			else
			{
				gui.displayBDeathScreen(GameMap.pChess[cursorPos.X][cursorPos.Y], deadB++);
			}			
			GameMap.pChess[cursorPos.X][cursorPos.Y]->setAlive(false);			
		}
		move(chessPos, cursorPos);
		GameMap.pChess[cursorPos.X][cursorPos.Y]->Promote(); //�h�L����ﭱ���u�i�H����

		WhosTurn = !WhosTurn; //�������b�^�X�A�洫�X�Ѥ�
		return true;
	}
	else if (GameMap.pChess[chessPos.X][chessPos.Y]->isCastling(cursorPos, GameMap))
	{
		if (gui.showConfirm("      �������� ?      ")) 
		{
			COORD castling = ComXY((chessPos.X > cursorPos.X ? -2 : 2), (chessPos.X > cursorPos.X ? 3 : -2));
			move(chessPos, ComXY((chessPos.X + castling.X), chessPos.Y));
			move(cursorPos, ComXY((cursorPos.X + castling.Y), cursorPos.Y));
			WhosTurn = !WhosTurn; //�������b�^�X�A�洫�X�Ѥ�			
		}
		return true;
	}
	else if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL) 
	{
		if (GameMap.pChess[cursorPos.X][cursorPos.Y]->getColor() == GameMap.pChess[chessPos.X][chessPos.Y]->getColor())  //���O���P���
		{
			return true;
		}
	}
		
	return false;
}

void Game::move(COORD oriPos, COORD movePos)
{
	GameMap.pChess[movePos.X][movePos.Y] = GameMap.pChess[oriPos.X][oriPos.Y];		//�л\pointer
	GameMap.pChess[oriPos.X][oriPos.Y] = NULL;							            //�R���쥻��m��pointer
	GameMap.pChess[movePos.X][movePos.Y]->setPos(movePos);						    //���Chess����m
	GameMap.pChess[movePos.X][movePos.Y]->Moved();									//���ʤ@��	
}

void Game::ArtificialIntelligence() 
{
	//��Ѥl

	//�ʧ@
}