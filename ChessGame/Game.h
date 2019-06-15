#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()

COORD ComXY(SHORT x, SHORT y);    //�Nx, y�ন sturctor COORD
struct Moving
{
	COORD from;
	COORD to;
};

class Game
{
public:
	Game();
	void Interface();			//��ܹC������	
	
private:
	void reset();
	void start();				//����C��
	void exitGame();			//���}�C��
	void playerControl();		//�i�J���a����
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