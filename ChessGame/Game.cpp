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
			COORD savePos = cursorPos;

			// 這裡寫AI
			if (ArtificialIntelligence())
			{
				if (!GameMap.get_King(false)->getAlive())
				{ 
					Sleep(1000); gui.showAlert("       黑方勝利       ", 5000); 
					return;
				}
				else  // 回合結束，換邊 顯示畫面
				{
					WhosTurn = !WhosTurn;					
					gui.displayChessboard(GameMap);
					gui.displayGameInfo(WhosTurn, GameMap);					
				}
			}

			cursorPos = savePos;
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
		move(chessPos, cursorPos, false);
		GameMap.pChess[cursorPos.X][cursorPos.Y]->Promote(); //士兵走到對面底線可以升變

		WhosTurn = !WhosTurn; //完成此半回合，交換出棋方
		return true;
	}
	else if (GameMap.pChess[chessPos.X][chessPos.Y]->isCastling(cursorPos, GameMap))
	{
		if (gui.showConfirm("      王車易位 ?      ")) 
		{
			COORD castling = ComXY((chessPos.X > cursorPos.X ? -2 : 2), (chessPos.X > cursorPos.X ? 3 : -2));
			move(chessPos, ComXY((chessPos.X + castling.X), chessPos.Y), false);
			move(cursorPos, ComXY((cursorPos.X + castling.Y), cursorPos.Y), false);
			WhosTurn = !WhosTurn; //完成此半回合，交換出棋方			
		}
		return true;
	}
	else if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL) 
	{
		if (GameMap.pChess[cursorPos.X][cursorPos.Y]->getColor() == GameMap.pChess[chessPos.X][chessPos.Y]->getColor())  //選到別的同色棋
		{
			if (AI == true && WhosTurn == true) { return false; }
			return true;
		}
	}
		
	return false;
}

bool Game::AImoveChess()
{
	if (GameMap.pChess[chessPos.X][chessPos.Y]->isValid(cursorPos, GameMap)) //移動狀況
	{
		if (GameMap.pChess[chessPos.X][chessPos.Y]->isPassing(cursorPos.X, GameMap))
		{			
			GameMap.pChess[cursorPos.X][chessPos.Y]->setAlive(false);
			GameMap.pChess[cursorPos.X][chessPos.Y] = NULL;
		}
		if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL) //吃子狀況	
		{			
			GameMap.pChess[cursorPos.X][cursorPos.Y]->setAlive(false);
		}
		move(chessPos, cursorPos, true);
		GameMap.pChess[cursorPos.X][cursorPos.Y]->Promote(); //士兵走到對面底線可以升變
		
		return true;
	}	
	else if (GameMap.pChess[cursorPos.X][cursorPos.Y] != NULL)
	{
		if (GameMap.pChess[cursorPos.X][cursorPos.Y]->getColor() == GameMap.pChess[chessPos.X][chessPos.Y]->getColor())  //選到別的同色棋
		{
			if (AI == true && WhosTurn == true) { return false; }
			return true;
		}
	}

	return false;
}

void Game::move(COORD oriPos, COORD movePos, bool AI)
{
	GameMap.pChess[movePos.X][movePos.Y] = GameMap.pChess[oriPos.X][oriPos.Y];		//覆蓋pointer
	GameMap.pChess[oriPos.X][oriPos.Y] = NULL;							            //刪除原本位置的pointer

	if (AI != true) 
	{
		GameMap.pChess[movePos.X][movePos.Y]->setPos(movePos);						//更改Chess的位置
		GameMap.pChess[movePos.X][movePos.Y]->Moved();								//移動一次
	}	
}

bool Game::ArtificialIntelligence() 
{
	try{
		Moving bestMove = minimaxRoot(3, true);
		move(bestMove.from, bestMove.to, false);
		return true;
	}
	catch (exception ex) 
	{
		return false;
	}	
}

Moving Game::minimaxRoot(int depth, bool isMaximisingPlayer)
{
	// var newGameMoves = game.ugly_moves();
	Moving *newGameMoves = getAllMoves();
	int BestValue = -99999;
	Moving BestMoveFound;

	for (int i = 0; i < sizeof(newGameMoves); i++) 
	{
		Moving newGameMove = newGameMoves[i];
		//// game.ugly_move(newGameMove);
		// set new map
		Chess *ch[ROW_SIZE][COLUMN_SIZE];
		int deadb=0, deadw=0;
		saveMap(ch, deadb, deadw);
		// set chessPos, cusorPos
		chessPos = newGameMove.from;
		cursorPos = newGameMove.to;
		//move
		AImoveChess();
		
		int value = minimax(depth - 1, -100000, 100000, !isMaximisingPlayer);
		
		//// game.undo();
		redoMap(ch, deadb, deadw);

		if (value >= BestValue) {
			BestValue = value;
			BestMoveFound = newGameMove;
		}
	}
	delete[] newGameMoves;
	return BestMoveFound;
}

int Game::minimax(int depth,  int alpha, int beta, bool isMaximisingPlayer)
{
	if (depth == 0) {
		int totalEvaluation = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				COORD moveP = ComXY(i, j);
				totalEvaluation = totalEvaluation + getPieceValue(moveP);
			}
		}
		return -totalEvaluation;
	}

	// var newGameMoves = game.ugly_moves();
	Moving *newGameMoves = getAllMoves();

	if (isMaximisingPlayer) {
		int bestMove = -99999;
		for (int i = 0; i < sizeof(newGameMoves); i++) {
			////game.ugly_move(newGameMoves[i]);
			// set new map
			Chess *ch[ROW_SIZE][COLUMN_SIZE];
			int deadb=0, deadw=0;
			saveMap(ch, deadb, deadw);
			// set chessPos, cusorPos
			chessPos = newGameMoves[i].from;
			cursorPos = newGameMoves[i].to;
			//move
			AImoveChess();
			//move(newGameMoves[i].from, newGameMoves[i].to);			

			////bestMove = Math.max(bestMove, minimax(depth - 1, alpha, beta, !isMaximisingPlayer));
			int mim = minimax(depth - 1, alpha, beta, !isMaximisingPlayer);
			bestMove = bestMove > mim ? bestMove : mim;						
			
			////game.undo();
			redoMap(ch, deadb, deadw);
			//move(newGameMoves[i].to, newGameMoves[i].from);

			////alpha = Math.max(alpha, bestMove);
			alpha = alpha > bestMove ? alpha : bestMove;
			

			if (beta <= alpha) 
			{
				delete[] newGameMoves;
				return bestMove;
			}
		}
		delete[] newGameMoves;
		return bestMove;
	}
	else {
		int bestMove = 99999;
		for (int i = 0; i < sizeof(newGameMoves); i++) {
			
			////game.ugly_move(newGameMoves[i]);
			// set new map
			Chess *ch[ROW_SIZE][COLUMN_SIZE];
			int deadb=0, deadw=0;
			saveMap(ch, deadb, deadw);
			// set chessPos, cusorPos
			chessPos = newGameMoves[i].from;
			cursorPos = newGameMoves[i].to;
			//move
			AImoveChess();
			//move(newGameMoves[i].from, newGameMoves[i].to);

			////bestMove = Math.min(bestMove, minimax(depth - 1, alpha, beta, !isMaximisingPlayer));
			int mim = minimax(depth - 1, alpha, beta, !isMaximisingPlayer);
			bestMove = bestMove < mim ? bestMove : mim;
			
			////game.undo();
			redoMap(ch, deadb, deadw);
			//move(newGameMoves[i].to, newGameMoves[i].from);

			////beta = Math.min(beta, bestMove);
			beta = alpha < bestMove ? beta : bestMove;			

			if (beta <= alpha) 
			{
				delete[] newGameMoves;
				return bestMove;
			}
		}
		delete[] newGameMoves;
		return bestMove;
	}
}

Moving* Game::getAllMoves()
{
	Moving *allMoves = new Moving[9999];
	int index = 0;	

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			COORD from = ComXY(i, j);
			chessPos = from;

			if (GameMap.pChess[chessPos.X][chessPos.Y] != NULL && GameMap.pChess[chessPos.X][chessPos.Y]->getColor() == WhosTurn)
			{
				for (int p = 0; p < ROW_SIZE; p++)
				{
					for (int q = 0; q < COLUMN_SIZE; q++)
					{
						COORD to = ComXY(p, q);						
						cursorPos = to;

						Chess *ch[ROW_SIZE][COLUMN_SIZE];
						int deadb = 0, deadw = 0;
						saveMap(ch, deadb, deadw);
						
						if (!(from.X == to.X && from.Y == to.Y) && AImoveChess())
						{							
							allMoves[index].from = from;
							allMoves[index].to = to;
							index++;

							redoMap(ch, deadb, deadw);
						}
					}
				}
			}
		}
	}
	return allMoves;
}

int Game::getPieceValue(COORD moveP)
{
	Chess *ch = GameMap.pChess[moveP.X][moveP.Y];
	if (ch == NULL) 
	{
		return 0;
	}
	else 
	{
		int absoluteValue = getAbsoluteValue(ch, ch->getColor() == false, moveP);
		return ch->getColor() == false ? absoluteValue : -absoluteValue;
	}	
}

int Game::getAbsoluteValue(Chess *ch, bool isWhite, COORD moveP)
{
	int chessEval = isWhite ? ch->getEvaluation(moveP.X, moveP.Y) : ch->getEvaluation(ROW_SIZE - moveP.X - 1, COLUMN_SIZE - moveP.Y - 1);
	if (ch->getName() == "Ｐ") { return 100 + chessEval; }
	else if (ch->getName() == "Ｒ") { return 500 + chessEval; }
	else if (ch->getName() == "Ｎ") { return 300 + chessEval; }
	else if (ch->getName() == "Ｂ") { return 300 + chessEval; }
	else if (ch->getName() == "Ｑ") { return 900 + chessEval; }
	else if (ch->getName() == "Ｋ") { return 9000 + chessEval; }
	else { return 0; }	
}

void Game::saveMap(Chess *ch[ROW_SIZE][COLUMN_SIZE], int &deadb, int &deadw)
{
	deadb = deadB;
	deadw = deadW;
	for (int s = 0; s < ROW_SIZE; s++)
	{
		for (int r = 0; r < COLUMN_SIZE; r++)
		{
			ch[s][r] = GameMap.pChess[s][r];
		}
	}
}

void Game::redoMap(Chess *ch[ROW_SIZE][COLUMN_SIZE], int deadb, int deadw) 
{
	deadB = deadb;
	deadW = deadw;
	for (int s = 0; s < ROW_SIZE; s++)
	{
		for (int r = 0; r < COLUMN_SIZE; r++)
		{
			GameMap.pChess[s][r] = ch[s][r];
		}
	}
}