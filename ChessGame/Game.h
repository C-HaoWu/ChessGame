#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()

COORD ComXY(SHORT x, SHORT y);    //將x, y轉成 sturctor COORD

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
	void move(COORD, COORD);
	void ArtificialIntelligence();
	int minimaxRoot(int, bool);
	int minimax(int, int, int, bool);
	int getPieceValue(COORD);
	Moving* getAllMoves();

	COORD cursorPos, chessPos;
	Map GameMap;
	bool WhosTurn;
	bool AI;
	int deadB;
	int deadW;
	GUI gui;
};
#endif