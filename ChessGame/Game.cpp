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
	WhosTurn = false;  //白棋先行	
	cursorPos = ComXY(0, 7);
	chessPos = ComXY(0, 0); 
	int deadB = 0;
	int deadW = 0;
}

void Game::Interface() //開始介面
{
	while (true)
	{
		switch (gui.mainMenu()) {
		case 1:
			AI = false;
			start(); //開始遊戲
			break;
		case 2:
			gui.displayAboutScreen(); //顯示關於
			break;
		case 3:
			exitGame(); //離開遊戲
			break;
		case 4:
			AI = true;
			start(); //開始遊戲
			break;
		default:
			break;
		}
	}
}

void Game::start()
{
	system("cls");      //清除開始介面畫面

	gui.setVisible(true);                           //顯示游標
	gui.dwSize(15);									//設定游標大小
	gui.displayGameScreen(GameMap, WhosTurn);		//顯示遊戲畫面

	playerControl();    //進入玩家控制
	reset();			//遊戲結束後重置
}

void Game::reset()  //重設棋盤、回合數、復活棋子
{
	GameMap.reset();
	WhosTurn = false;
	cursorPos = ComXY(0, 7);
	chessPos = ComXY(0, 0);
	int deadB = 0;
	int deadW = 0;
}

void Game::exitGame() //離開遊戲
{
	system("cls");
	gui.displayExitScreen();
	Sleep(200);//Delay 200ms
	exit(EXIT_SUCCESS);
}

void Game::playerControl() //選棋階段
{
	bool oriTurn = false;
	bool isCatchChess = false;
	gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 2, CHESS_BOARD_Y + cursorPos.Y);
	gui.displayGameScreen(GameMap, WhosTurn);
	
	while (true)  //用鍵盤控制 cursorPos 來改變 GameMap
	{
		if (AI == true && WhosTurn == true) 
		{
			// 這裡寫AI
			if (gui.MenuInGame()) 
			{
				// 回合結束，換邊 顯示畫面
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
					if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL && GameMap.pChess[cursorPos.X][cursorPos.Y]->getColor() == WhosTurn) //選棋階段選到同色棋子上
					{
						gui.displayGameInfo(WhosTurn, GameMap, GameMap.pChess[cursorPos.X][cursorPos.Y]);
						gui.displayPossiblePath(GameMap.pChess[cursorPos.X][cursorPos.Y], GameMap); //顯示可以走的位置

						gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 2, CHESS_BOARD_Y + cursorPos.Y);
						chessPos = cursorPos;
						isCatchChess = true;
					}
				}
				else if (moveChess()) //移動成功	
				{
					gui.displayChessboard(GameMap);
					gui.displayGameInfo(WhosTurn, GameMap);
					isCatchChess = false;
					if (oriTurn == WhosTurn) { continue; } //選擇另一個棋子，回到選棋模式並直接進入case Enter

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

					if (!GameMap.get_King(true)->getAlive()) { Sleep(1000); gui.showAlert("       白方勝利       ", 5000); return; }
					if (!GameMap.get_King(false)->getAlive()) { Sleep(1000); gui.showAlert("       黑方勝利       ", 5000); return; }
				}
				break;
			case KB_ESC: //呼叫選單
				switch (gui.MenuInGame()) {
				case 1: //resume
					break;
				case 2: //restart
					if (gui.showConfirm("    確定重新開始 ?    ")) { //22 chars
						reset();
						gui.displayGameScreen(GameMap, WhosTurn);
					}
					break;
				case 3: //back to main menu
					if (gui.showConfirm("  確定放棄目前戰局 ?  "))
						return;
					break;
				case 4: //exit
					if (gui.showConfirm("      確定離開 ?      "))
						exitGame();
				default:
					break;
				}
				break;
			default:
				break;
			}
			gui.gotoxy(CHESS_BOARD_X + cursorPos.X * 2, CHESS_BOARD_Y + cursorPos.Y); //改變游標位置
			gui.setVisible(true);			
		}		
	}
}

bool Game::moveChess() //確定移動
{
	if (GameMap.pChess[chessPos.X][chessPos.Y]->isValid(cursorPos, GameMap)) //移動狀況
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
		if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL) //吃子狀況	
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
		GameMap.pChess[cursorPos.X][cursorPos.Y]->Promote(); //士兵走到對面底線可以升變

		WhosTurn = !WhosTurn; //完成此半回合，交換出棋方
		return true;
	}
	else if (GameMap.pChess[chessPos.X][chessPos.Y]->isCastling(cursorPos, GameMap))
	{
		if (gui.showConfirm("      王車易位 ?      ")) 
		{
			COORD castling = ComXY((chessPos.X > cursorPos.X ? -2 : 2), (chessPos.X > cursorPos.X ? 3 : -2));
			move(chessPos, ComXY((chessPos.X + castling.X), chessPos.Y));
			move(cursorPos, ComXY((cursorPos.X + castling.Y), cursorPos.Y));
			WhosTurn = !WhosTurn; //完成此半回合，交換出棋方			
		}
		return true;
	}
	else if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL) 
	{
		if (GameMap.pChess[cursorPos.X][cursorPos.Y]->getColor() == GameMap.pChess[chessPos.X][chessPos.Y]->getColor())  //選到別的同色棋
		{
			return true;
		}
	}
		
	return false;
}

void Game::move(COORD oriPos, COORD movePos)
{
	GameMap.pChess[movePos.X][movePos.Y] = GameMap.pChess[oriPos.X][oriPos.Y];		//覆蓋pointer
	GameMap.pChess[oriPos.X][oriPos.Y] = NULL;							            //刪除原本位置的pointer
	GameMap.pChess[movePos.X][movePos.Y]->setPos(movePos);						    //更改Chess的位置
	GameMap.pChess[movePos.X][movePos.Y]->Moved();									//移動一次	
}

void Game::ArtificialIntelligence() 
{
	//選棋子

	//動作
}