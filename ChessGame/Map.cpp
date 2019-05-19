#include "Map.h"
#include "Game.h"
#include "Chess.h"

Map::Map()
{
	setup();
}

Map::~Map()
{
	empty();
}

Chess* Map::get_King(bool color) const
{
	if (color)
		return bKing;
	else
		return wKing;
}

bool Map::isChecking(bool color) const
{
	return get_King(color)->isChecking(*this);
}

void Map::reset()
{
	empty();
	setup();
}

void Map::setup()
{
	for (int i = 0; i < ROW_SIZE; i++)
		for (int j = 0; j < COLUMN_SIZE; j++)
			pChess[i][j] = NULL;

	bKing = new King("��", true, ComXY(4, 0));				pChess[4][0] = bKing;
	wKing = new King("��", false, ComXY(4, 7));				pChess[4][7] = wKing;
	bQueen = new Queen("��", true, ComXY(3, 0));			pChess[3][0] = bQueen;
	wQueen = new Queen("��", false, ComXY(3, 7));			pChess[3][7] = wQueen;
	bBishop1 = new Bishop("��", true, ComXY(2, 0));			pChess[2][0] = bBishop1;
	bBishop2 = new Bishop("��", true, ComXY(5, 0));			pChess[5][0] = bBishop2;
	wBishop1 = new Bishop("��", false, ComXY(2, 7));		pChess[2][7] = wBishop1;
	wBishop2 = new Bishop("��", false, ComXY(5, 7));		pChess[5][7] = wBishop2;
	bRook1 = new Rook("��", true, ComXY(0, 0));				pChess[0][0] = bRook1;
	bRook2 = new Rook("��", true, ComXY(7, 0));				pChess[7][0] = bRook2;
	wRook1 = new Rook("��", false, ComXY(0, 7));			pChess[0][7] = wRook1;
	wRook2 = new Rook("��", false, ComXY(7, 7));			pChess[7][7] = wRook2;
	bKnight1 = new Knight("��", true, ComXY(1, 0));			pChess[1][0] = bKnight1;
	bKnight2 = new Knight("��", true, ComXY(6, 0));			pChess[6][0] = bKnight2;
	wKnight1 = new Knight("��", false, ComXY(1, 7));		pChess[1][7] = wKnight1;
	wKnight2 = new Knight("��", false, ComXY(6, 7));		pChess[6][7] = wKnight2;
	bPawn1 = new Pawn("��", true, ComXY(0, 1));				pChess[0][1] = bPawn1;
	bPawn2 = new Pawn("��", true, ComXY(1, 1));				pChess[1][1] = bPawn2;
	bPawn3 = new Pawn("��", true, ComXY(2, 1));				pChess[2][1] = bPawn3;
	bPawn4 = new Pawn("��", true, ComXY(3, 1));				pChess[3][1] = bPawn4;
	bPawn5 = new Pawn("��", true, ComXY(4, 1));				pChess[4][1] = bPawn5;
	bPawn6 = new Pawn("��", true, ComXY(5, 1));				pChess[5][1] = bPawn6;
	bPawn7 = new Pawn("��", true, ComXY(6, 1));				pChess[6][1] = bPawn7;
	bPawn8 = new Pawn("��", true, ComXY(7, 1));				pChess[7][1] = bPawn8;
	wPawn1 = new Pawn("��", false, ComXY(0, 6));			pChess[0][6] = wPawn1;
	wPawn2 = new Pawn("��", false, ComXY(1, 6));			pChess[1][6] = wPawn2;
	wPawn3 = new Pawn("��", false, ComXY(2, 6));			pChess[2][6] = wPawn3;
	wPawn4 = new Pawn("��", false, ComXY(3, 6));			pChess[3][6] = wPawn4;
	wPawn5 = new Pawn("��", false, ComXY(4, 6));			pChess[4][6] = wPawn5;
	wPawn6 = new Pawn("��", false, ComXY(5, 6));			pChess[5][6] = wPawn6;
	wPawn7 = new Pawn("��", false, ComXY(6, 6));			pChess[6][6] = wPawn7;
	wPawn8 = new Pawn("��", false, ComXY(7, 6));			pChess[7][6] = wPawn8;
}

void Map::empty()
{
	delete bKing;
	delete wKing;
	delete bQueen;
	delete wQueen;
	delete bBishop1;
	delete bBishop2;
	delete wBishop1;
	delete wBishop2;
	delete bRook1;
	delete bRook2;
	delete wRook1;
	delete wRook2;
	delete bKnight1;
	delete bKnight2;
	delete wKnight1;
	delete wKnight2;
	delete bPawn1;
	delete bPawn2;
	delete bPawn3;
	delete bPawn4;
	delete bPawn5;
	delete bPawn6;
	delete bPawn7;
	delete bPawn8;
	delete wPawn1;
	delete wPawn2;
	delete wPawn3;
	delete wPawn4;
	delete wPawn5;
	delete wPawn6;
	delete wPawn7;
	delete wPawn8;
}