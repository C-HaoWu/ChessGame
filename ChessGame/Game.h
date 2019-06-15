#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()

COORD ComXY(SHORT x, SHORT y);    //將x, y轉成 sturctor COORD
struct Moving
{
	COORD from;
	COORD to;
};

class Game
{
public:
	Game();
	void Interface();			//顯示遊戲介面	
	
private:
	void reset();
	void start();				//執行遊戲
	void exitGame();			//離開遊戲
	void playerControl();		//進入玩家控制
	bool moveChess();
	bool AImoveChess();
	void move(COORD, COORD, bool);
	bool ArtificialIntelligence();
	Moving minimaxRoot(int, bool);
	int minimax(int, int, int, bool);
	Moving* getAllMoves();
	int getPieceValue(COORD);	
	int getAbsoluteValue(Chess*, bool, COORD);

	COORD cursorPos, chessPos;
	Map GameMap;
	bool WhosTurn;
	bool AI;
	int deadB;
	int deadW;
	GUI gui;
	void saveMap(Chess *ch[ROW_SIZE][COLUMN_SIZE], int&, int&);
	void redoMap(Chess *ch[ROW_SIZE][COLUMN_SIZE], int, int);
};
#endif