#ifndef CHESS_H
#define CHESS_H
#include <vector>
#include <string>
#include <Windows.h>
#define ROW_SIZE 8
#define COLUMN_SIZE 8

using std::string;
class Map;

struct relativePosition
{
	short rightx;
	short leftx;
	short upy;
	short downy;
};

class Chess
{
public:
	Chess() = delete;
	Chess(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	~Chess();

	void setName(string);
	void setAlive(bool);
	string getName() const;
	COORD getPos() const;
	bool getAlive() const;
	bool getColor() const;
	int getMoved() const;
	void Moved();  //每移動一次 moved 加一
	int getEvaluation(SHORT, SHORT)const;
	
	relativePosition rP(COORD) const; 
	bool isChecking(COORD, const Map&) const;  //是否被控制 
	bool isChecking(const Map&) const;		   //多載
	
	virtual void setPos(COORD p);
	virtual void Promote();  //士兵升變
	virtual bool isPassing(SHORT, const Map&) const;   //判斷是否可以吃過路兵
	virtual bool isCastling(COORD, const Map&) const;  //判斷是否可以入堡
	virtual bool isValid(COORD, const Map&) const = 0; //走法是否合法
private:
	string Name; //棋子名
	bool Color;  //黑為true 白為false
	COORD Pos;   //size (8,8)內
	bool alive;  //棋子死活
	int moved;   //是否移動	
	int Evaluation[ROW_SIZE][COLUMN_SIZE]; //位置評估值，for AI
};

class King : public Chess  // 國王
{
public:
	King() = delete;
	~King();
	King(string, bool, COORD, int [ROW_SIZE][COLUMN_SIZE]);
	virtual bool isCastling(COORD, const Map&) const;
	virtual bool isValid(COORD, const Map&) const;
};

class Queen : public Chess // 皇后
{
public:
	Queen() = delete;
	~Queen();
	Queen(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual void setPos(COORD p);
	virtual bool isValid(COORD, const Map&) const;
private:
	Chess* rookTest;  //內部有城堡和主教
	Chess* bishopTest;
};

class Rook : public Chess // 城堡
{
public:
	Rook() = delete;
	~Rook();
	Rook(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual bool isValid(COORD, const Map&) const;
};

class Bishop : public Chess // 主教
{
public:
	Bishop() = delete;
	~Bishop();
	Bishop(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual bool isValid(COORD, const Map&) const;
};

class Knight : public Chess // 騎士
{
public:
	Knight() = delete;
	~Knight();
	Knight(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual bool isValid(COORD, const Map&) const;
};

class Pawn :public Chess  // 士兵
{
public:
	Pawn() = delete;
	~Pawn();
	Pawn(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual void Promote();
	virtual bool isPassing(SHORT, const Map&) const;
	virtual void setPos(COORD);
	virtual bool isValid(COORD, const Map&) const;
private:
	Chess* Promotion[4]; //內部有可升變的四種棋
};

#endif