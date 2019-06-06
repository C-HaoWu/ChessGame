#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include <iostream>
#include <string>
#include "Map.h"
#include "GUI.h"
#include <conio.h>   // _getch()

COORD ComXY(SHORT x, SHORT y);    //�Nx, y�ন sturctor COORD

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