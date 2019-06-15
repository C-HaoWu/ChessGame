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
	void Moved();  //�C���ʤ@�� moved �[�@
	int getEvaluation(SHORT, SHORT)const;
	
	relativePosition rP(COORD) const; 
	bool isChecking(COORD, const Map&) const;  //�O�_�Q���� 
	bool isChecking(const Map&) const;		   //�h��
	
	virtual void setPos(COORD p);
	virtual void Promote();  //�h�L����
	virtual bool isPassing(SHORT, const Map&) const;   //�P�_�O�_�i�H�Y�L���L
	virtual bool isCastling(COORD, const Map&) const;  //�P�_�O�_�i�H�J��
	virtual bool isValid(COORD, const Map&) const = 0; //���k�O�_�X�k
private:
	string Name; //�Ѥl�W
	bool Color;  //�¬�true �լ�false
	COORD Pos;   //size (8,8)��
	bool alive;  //�Ѥl����
	int moved;   //�O�_����	
	int Evaluation[ROW_SIZE][COLUMN_SIZE]; //��m�����ȡAfor AI
};

class King : public Chess  // ���
{
public:
	King() = delete;
	~King();
	King(string, bool, COORD, int [ROW_SIZE][COLUMN_SIZE]);
	virtual bool isCastling(COORD, const Map&) const;
	virtual bool isValid(COORD, const Map&) const;
};

class Queen : public Chess // �ӦZ
{
public:
	Queen() = delete;
	~Queen();
	Queen(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual void setPos(COORD p);
	virtual bool isValid(COORD, const Map&) const;
private:
	Chess* rookTest;  //�����������M�D��
	Chess* bishopTest;
};

class Rook : public Chess // ����
{
public:
	Rook() = delete;
	~Rook();
	Rook(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual bool isValid(COORD, const Map&) const;
};

class Bishop : public Chess // �D��
{
public:
	Bishop() = delete;
	~Bishop();
	Bishop(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual bool isValid(COORD, const Map&) const;
};

class Knight : public Chess // �M�h
{
public:
	Knight() = delete;
	~Knight();
	Knight(string, bool, COORD, int[ROW_SIZE][COLUMN_SIZE]);
	virtual bool isValid(COORD, const Map&) const;
};

class Pawn :public Chess  // �h�L
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
	Chess* Promotion[4]; //�������i���ܪ��|�ش�
};

#endif