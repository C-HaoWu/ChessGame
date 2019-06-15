#include "Chess.h"
#include "Game.h"
#include "Map.h"
#include <math.h>
#include <iostream>
using namespace std;

GUI gui;

Chess::Chess(string iName, bool icolor, COORD iPos, int iEval[ROW_SIZE][COLUMN_SIZE])
	: Name(iName), Color(icolor), Pos(iPos), alive(true), moved(0), Evaluation() {}

King::King(string iName, bool icolor, COORD iPos, int iEval[ROW_SIZE][COLUMN_SIZE]) : Chess(iName, icolor, iPos, iEval) {}
Queen::Queen(string iName, bool icolor, COORD iPos, int iEval[ROW_SIZE][COLUMN_SIZE]) : Chess(iName, icolor, iPos, iEval)
{
	rookTest = new Rook(iName, icolor, iPos, iEval);
	bishopTest = new Bishop(iName, icolor, iPos, iEval);
}
Rook::Rook(string iName, bool icolor, COORD iPos, int iEval[ROW_SIZE][COLUMN_SIZE]) : Chess(iName, icolor, iPos, iEval) {}
Bishop::Bishop(string iName, bool icolor, COORD iPos, int iEval[ROW_SIZE][COLUMN_SIZE]) : Chess(iName, icolor, iPos, iEval) {}
Knight::Knight(string iName, bool icolor, COORD iPos, int iEval[ROW_SIZE][COLUMN_SIZE]) : Chess(iName, icolor, iPos, iEval) {}
Pawn::Pawn(string iName, bool icolor, COORD iPos, int iEval[ROW_SIZE][COLUMN_SIZE]) : Chess(iName, icolor, iPos, iEval)
{
	Promotion[0] = new Queen("Ｑ", icolor, iPos, iEval);
	Promotion[1] = new Knight("Ｎ", icolor, iPos, iEval);
	Promotion[2] = new Rook("Ｒ", icolor, iPos, iEval);
	Promotion[3] = new Bishop("Ｂ", icolor, iPos, iEval);
}

Chess::~Chess() {}
King::~King() {}
Queen::~Queen()
{
	delete rookTest;
	delete bishopTest;
}
Rook::~Rook() {}
Bishop::~Bishop() {}
Knight::~Knight() {}
Pawn::~Pawn() { delete[] *Promotion; }

relativePosition Chess::rP(COORD moveP) const
{
	relativePosition RP;
	if (moveP.X > getPos().X)
	{
		RP.leftx = getPos().X;
		RP.rightx = moveP.X;
	}
	else
	{
		RP.leftx = moveP.X;
		RP.rightx = getPos().X;
	}
	if (moveP.Y > getPos().Y)
	{
		RP.upy = getPos().Y;
		RP.downy = moveP.Y;
	}
	else
	{
		RP.upy = moveP.Y;
		RP.downy = getPos().Y;
	}
	return RP;
}

void Chess::setName(string name) { Name = name; }
void Chess::setPos(COORD p) { Pos = p; }
void Chess::setAlive(bool a) { alive = a; }
string Chess::getName() const { return Name; }
bool Chess::getColor() const { return Color; }
COORD Chess::getPos() const { return Pos; }
int Chess::getMoved() const { return moved; }
int Chess::getEvaluation(SHORT x, SHORT y) const { return Evaluation[x][y]; }
void Chess::Moved() { moved++; }
void Chess::Promote() {}
bool Chess::getAlive() const { return alive; }
bool Chess::isPassing(SHORT x, const Map& map) const { return false; }
bool Chess::isCastling(COORD moveP, const Map& map) const { return false; }

bool Chess::isChecking(const Map& map) const
{
	return isChecking(getPos(), map);
}

bool Chess::isChecking(COORD checkPos, const Map& map) const
{
	for (SHORT i = 0; i < ROW_SIZE; i++)
		for (SHORT j = 0; j < COLUMN_SIZE; j++)
			if (map.pChess[i][j] != NULL && map.pChess[i][j]->getColor() != getColor()) {
				if (map.pChess[i][j]->getName() == "Ｐ") {
					if (abs(i - checkPos.X) == 1 && (j - checkPos.Y) == (getColor() ? 1 : -1))
						return true;
				}
				else if (map.pChess[i][j]->isValid(checkPos, map))
					return true;
			}
	return false;
}

bool King::isCastling(COORD moveP, const Map& map) const //若原本的棋子為國王，有入堡跟違規移動的特殊狀況
{														 //入堡，有三個條件 -> 條件一: 國王跟城堡都還沒移動過  
	Chess *ch = map.pChess[moveP.X][moveP.Y];			 //					   條件二: 國王與城堡間沒有其他棋子
	relativePosition rp = rP(moveP);					 //					   條件三: 國王所在的格、易位時國王將要經過的格、易位後國王將占據的格，都不能受到對方任何棋子的check。

	if (ch != NULL && ch->getName() == "Ｒ" && getColor() == ch->getColor() && !(getMoved() || ch->getMoved() || isChecking(map)))
	{
		for (int i = rp.leftx + 1; i < rp.rightx; i++)
		{
			if (map.pChess[i][(getColor() ? 0 : 7)] != NULL)
				return false;
			if (rp.rightx - i < 3)
				if (isChecking(ComXY(i, (getColor() ? 0 : 7)), map))
					return false;
		}
		return true;
	}
	return false;
}

bool King::isValid(COORD moveP, const Map& map) const //國王
{
	Chess *ch = map.pChess[moveP.X][moveP.Y];
	COORD distance = ComXY(abs(moveP.X - getPos().X), abs(moveP.Y - getPos().Y));

	if ((ch != NULL && getColor() == ch->getColor())) //同色回傳false
		return false;
	if ((distance.X < 2 && distance.Y < 2) && (distance.X || distance.Y)) //八方
		return true;
	return false;
}

void Queen::setPos(COORD p)
{
	Chess::setPos(p);
	rookTest->setPos(p);
	bishopTest->setPos(p);
}

bool Queen::isValid(COORD moveP, const Map& map) const //皇后
{
	if (rookTest->isValid(moveP, map) || bishopTest->isValid(moveP, map)) //使用內部城堡及主教的確認函式
		return true;
	return false;
}

bool Rook::isValid(COORD moveP, const Map& map) const //城堡
{
	Chess *ch = map.pChess[moveP.X][moveP.Y];
	relativePosition rp = rP(moveP);
	if (ch != NULL && getColor() == ch->getColor()) //同色回傳false
		return false;
	if ((getPos().X - moveP.X) != 0 && (getPos().Y == moveP.Y)) //左右方向
	{
		for (int i = rp.leftx + 1; i < rp.rightx; i++)
			if (map.pChess[i][moveP.Y] != NULL)
				return false;
		return true;
	}
	else if ((getPos().X == moveP.X) && (getPos().Y - moveP.Y) != 0) //上下方向
	{
		for (int i = rp.upy + 1; i < rp.downy; i++)
			if (map.pChess[moveP.X][i] != NULL)
				return false;
		return true;
	}
	return false;
}

bool Bishop::isValid(COORD moveP, const Map& map) const //主教
{
	Chess *ch = map.pChess[moveP.X][moveP.Y];
	COORD distance = ComXY(abs(moveP.X - getPos().X), abs(moveP.Y - getPos().Y));
	relativePosition rp = rP(moveP);

	if (ch != NULL && getColor() == ch->getColor()) //同色回傳false
		return false;
	if (distance.X != 0 && distance.X == distance.Y)
	{
		if ((moveP.X - getPos().X) == (moveP.Y - getPos().Y)) //左上、右下方向
		{
			for (int i = rp.leftx + 1; i < rp.rightx; i++)
				if (map.pChess[i][rp.upy + i - rp.leftx] != NULL)
					return false;
			return true;
		}
		else //右上、左下方向
		{
			for (int i = rp.leftx + 1; i < rp.rightx; i++)
				if (map.pChess[i][rp.downy - i + rp.leftx] != NULL)
					return false;
			return true;
		}
	}
	return false;
}

bool Knight::isValid(COORD moveP, const Map& map) const //騎士
{
	Chess *ch = map.pChess[moveP.X][moveP.Y];
	COORD distance = ComXY(abs(moveP.X - getPos().X), abs(moveP.Y - getPos().Y));

	if (ch != NULL && getColor() == ch->getColor()) //同色回傳false
		return false;
	if ((pow(distance.X, 2) + pow(distance.Y, 2)) == 5) //L型
		return true;
	return false;
}

bool Pawn::isPassing(SHORT x, const Map& map) const
{
	Chess* ch = map.pChess[x][getPos().Y];
	if (getName() == "Ｐ" && getPos().Y == (getColor() ? 4 : 3))
		if (ch != NULL && ch->getMoved() == 1)
			return true;
	return false;
}

void Pawn::Promote()
{
	if (getName() == "Ｐ" && getPos().Y == (getColor() ? 7 : 0))
		setName(Promotion[gui.displayUpgradeScreen() - 1]->getName());
}

void Pawn::setPos(COORD p) {
	Chess::setPos(p);
	for (int i = 0; i < 4; i++)
		Promotion[i]->setPos(p);
}

bool Pawn::isValid(COORD moveP, const Map& map) const
{
	if (getName() == "Ｐ") {
		Chess *ch = map.pChess[moveP.X][moveP.Y];
		COORD coord = getPos();
		COORD distance = ComXY(abs(moveP.X - getPos().X), abs(moveP.Y - getPos().Y));

		if (ch != NULL && getColor() == ch->getColor()) //同色回傳false
			return false;
		if ((moveP.X == getPos().X) && moveP.Y - getPos().Y == (getColor() ? 1 : -1)) //正前方一格
		{
			if (ch != NULL) return false;
			else return true;
		}
		if (!getMoved())
			if (moveP.X == getPos().X && moveP.Y - getPos().Y == (getColor() ? 2 : -2)) //第一步可正前方兩格
			{
				if (ch != NULL)
					return false;
				else if (map.pChess[moveP.X][moveP.Y + (getColor() ? -1 : 1)] != NULL) {
					return false;
				}
				else return true;
			}
		if ((distance.X == 1 && moveP.Y - getPos().Y == (getColor() ? 1 : -1)) && (ch != NULL || isPassing(moveP.X, map))) //斜前方敵對棋
			return true;
		return false;

	}
	else if (getName() == "Ｑ")
		return Promotion[0]->isValid(moveP, map);
	else if (getName() == "Ｎ")
		return Promotion[1]->isValid(moveP, map);
	else if (getName() == "Ｒ")
		return Promotion[2]->isValid(moveP, map);
	else
		return Promotion[3]->isValid(moveP, map);
}