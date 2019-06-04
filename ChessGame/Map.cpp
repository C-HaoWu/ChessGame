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

	int KingEvalWhite[ROW_SIZE][COLUMN_SIZE] = {
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
		{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
		{2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
		{2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}};
	int KingEvalBlack[ROW_SIZE][COLUMN_SIZE] = {};
	reverseArray(KingEvalWhite, KingEvalBlack);
	int QueenEval[ROW_SIZE][COLUMN_SIZE] = {
		{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}};
	int BishopEvalWhite[ROW_SIZE][COLUMN_SIZE] = { 
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
		{-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
		{-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
		{-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
		{-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}};
	int BishopEvalBlack[ROW_SIZE][COLUMN_SIZE] = {};
	reverseArray(BishopEvalWhite, BishopEvalBlack);
	int KnightEval[ROW_SIZE][COLUMN_SIZE] = {
		{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
		{-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
		{-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
		{-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
		{-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
		{-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
		{-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
		{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0} };
	int RookEvalWhite[ROW_SIZE][COLUMN_SIZE] = {
		{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
		{0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
		{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
		{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
		{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
		{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
		{-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
		{0.0,   0.0, 0.0,  0.5,  0.5,  0.0,  0.0,  0.0}};
	int RookEvalBlack[ROW_SIZE][COLUMN_SIZE] = {};
	reverseArray(RookEvalWhite, RookEvalBlack);
	int PawnEvalWhite[ROW_SIZE][COLUMN_SIZE] = {
		{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
		{5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
		{1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
		{0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
		{0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
		{0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
		{0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
		{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
	};
	int PawnEvalBlack[ROW_SIZE][COLUMN_SIZE] = {};
	reverseArray(PawnEvalWhite, PawnEvalBlack);

	bKing = new King("¢Ù", true, ComXY(4, 0), KingEvalBlack);				pChess[4][0] = bKing;
	wKing = new King("¢Ù", false, ComXY(4, 7), KingEvalWhite);				pChess[4][7] = wKing;
	bQueen = new Queen("¢ß", true, ComXY(3, 0), QueenEval);			pChess[3][0] = bQueen;
	wQueen = new Queen("¢ß", false, ComXY(3, 7), QueenEval);			pChess[3][7] = wQueen;
	bBishop1 = new Bishop("¢Ð", true, ComXY(2, 0), BishopEvalBlack);			pChess[2][0] = bBishop1;
	bBishop2 = new Bishop("¢Ð", true, ComXY(5, 0), BishopEvalBlack);			pChess[5][0] = bBishop2;
	wBishop1 = new Bishop("¢Ð", false, ComXY(2, 7), BishopEvalWhite);		pChess[2][7] = wBishop1;
	wBishop2 = new Bishop("¢Ð", false, ComXY(5, 7), BishopEvalWhite);		pChess[5][7] = wBishop2;
	bRook1 = new Rook("¢à", true, ComXY(0, 0), RookEvalBlack);				pChess[0][0] = bRook1;
	bRook2 = new Rook("¢à", true, ComXY(7, 0), RookEvalBlack);				pChess[7][0] = bRook2;
	wRook1 = new Rook("¢à", false, ComXY(0, 7), RookEvalWhite);			pChess[0][7] = wRook1;
	wRook2 = new Rook("¢à", false, ComXY(7, 7), RookEvalWhite);			pChess[7][7] = wRook2;
	bKnight1 = new Knight("¢Ü", true, ComXY(1, 0), KnightEval);			pChess[1][0] = bKnight1;
	bKnight2 = new Knight("¢Ü", true, ComXY(6, 0), KnightEval);			pChess[6][0] = bKnight2;
	wKnight1 = new Knight("¢Ü", false, ComXY(1, 7), KnightEval);		pChess[1][7] = wKnight1;
	wKnight2 = new Knight("¢Ü", false, ComXY(6, 7), KnightEval);		pChess[6][7] = wKnight2;
	bPawn1 = new Pawn("¢Þ", true, ComXY(0, 1), PawnEvalBlack);				pChess[0][1] = bPawn1;
	bPawn2 = new Pawn("¢Þ", true, ComXY(1, 1), PawnEvalBlack);				pChess[1][1] = bPawn2;
	bPawn3 = new Pawn("¢Þ", true, ComXY(2, 1), PawnEvalBlack);				pChess[2][1] = bPawn3;
	bPawn4 = new Pawn("¢Þ", true, ComXY(3, 1), PawnEvalBlack);				pChess[3][1] = bPawn4;
	bPawn5 = new Pawn("¢Þ", true, ComXY(4, 1), PawnEvalBlack);				pChess[4][1] = bPawn5;
	bPawn6 = new Pawn("¢Þ", true, ComXY(5, 1), PawnEvalBlack);				pChess[5][1] = bPawn6;
	bPawn7 = new Pawn("¢Þ", true, ComXY(6, 1), PawnEvalBlack);				pChess[6][1] = bPawn7;
	bPawn8 = new Pawn("¢Þ", true, ComXY(7, 1), PawnEvalBlack);				pChess[7][1] = bPawn8;
	wPawn1 = new Pawn("¢Þ", false, ComXY(0, 6), PawnEvalWhite);			pChess[0][6] = wPawn1;
	wPawn2 = new Pawn("¢Þ", false, ComXY(1, 6), PawnEvalWhite);			pChess[1][6] = wPawn2;
	wPawn3 = new Pawn("¢Þ", false, ComXY(2, 6), PawnEvalWhite);			pChess[2][6] = wPawn3;
	wPawn4 = new Pawn("¢Þ", false, ComXY(3, 6), PawnEvalWhite);			pChess[3][6] = wPawn4;
	wPawn5 = new Pawn("¢Þ", false, ComXY(4, 6), PawnEvalWhite);			pChess[4][6] = wPawn5;
	wPawn6 = new Pawn("¢Þ", false, ComXY(5, 6), PawnEvalWhite);			pChess[5][6] = wPawn6;
	wPawn7 = new Pawn("¢Þ", false, ComXY(6, 6), PawnEvalWhite);			pChess[6][6] = wPawn7;
	wPawn8 = new Pawn("¢Þ", false, ComXY(7, 6), PawnEvalWhite);			pChess[7][6] = wPawn8;
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

void reverseArray(int white[ROW_SIZE][COLUMN_SIZE], int black[ROW_SIZE][COLUMN_SIZE])
{
	for (int i = 0; i < ROW_SIZE; i++) {
		for (int j = 0; j < COLUMN_SIZE; j++) {
			black[i][j] = white[ROW_SIZE - i - 1][COLUMN_SIZE - j - 1];
		}
	}
}