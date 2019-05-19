#ifndef MAP_H
#define MAP_H
#include "Chess.h"
#include <vector>
#define ROW_SIZE 8
#define COLUMN_SIZE 8

class Map
{
public:
	Map();
	~Map();
	void setup();
	void empty();
	void reset();
	bool isChecking(bool) const;
	Chess* get_King(bool) const;
	Chess* pChess[ROW_SIZE][COLUMN_SIZE];
private:
	Chess* bKing;
	Chess* wKing;
	Chess* bQueen;
	Chess* wQueen;
	Chess* bRook1;
	Chess* bRook2;
	Chess* wRook1;
	Chess* wRook2;
	Chess* bBishop1;
	Chess* bBishop2;
	Chess* wBishop1;
	Chess* wBishop2;
	Chess* bKnight1;
	Chess* bKnight2;
	Chess* wKnight1;
	Chess* wKnight2;
	Chess* bPawn1;
	Chess* bPawn2;
	Chess* bPawn3;
	Chess* bPawn4;
	Chess* bPawn5;
	Chess* bPawn6;
	Chess* bPawn7;
	Chess* bPawn8;
	Chess* wPawn1;
	Chess* wPawn2;
	Chess* wPawn3;
	Chess* wPawn4;
	Chess* wPawn5;
	Chess* wPawn6;
	Chess* wPawn7;
	Chess* wPawn8;
};

#endif