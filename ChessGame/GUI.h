#pragma once
#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <string>
#include <iomanip> //setw()
#include <thread>
#include "Map.h"
using std::cout;
using std::string;

#define WINDOW_COLS 42
#define WINDOW_LINES 24
#define BATTLE_SITUATION_LINES 20
#define KB_UP 72     //��L��J�ƭ� �W
#define KB_DOWN 80   //��L��J�ƭ� �U
#define KB_LEFT 75   //��L��J�ƭ� ��
#define KB_RIGHT 77  //��L��J�ƭ� �k
#define KB_ENTER 13  //��L��J�ƭ� Enter
#define KB_ESC 27    //��L��J�ƭ� ESC
#define CHESSMAP_SIZE_ROW 16      //�ѽLROW    SIZE
#define CHESSMAP_SIZE_COLUMN 8   //�ѽLcolumn SIZE
#define WD_BLACK_BG_WHITE 240     //�¦r�զ�I��
#define WD_RED_BG_WHITE 252       //���r�զ�I��
#define WD_WHITE_BG_LGRAY 127     //�ծ�մ� ((�G�ǩ��զr
#define WD_BLACK_BG_LGRAY 112     //�ծ�´� ((�G�ǩ��¦r
#define WD_WHITE_BG_DGRAY 143     //�®�մ� ((�t�ǩ��զr
#define WD_BLACK_BG_DGRAY 128     //�®�´� ((�t�ǩ��¦r
#define WD_RED_BG_BLACK 12        //���r�¦�I��
#define WD_WHITE_BG_BLACK 15       //�զr�¦�I��
#define WD_OCEANBLUE_BG_BLACK 11  //���Ŧ�r�¦�I��
#define WD_GRAY_BG_BLACK 8        //�Ǧ�r�¦�I��
#define DEFAULT_COLOR 7           //�w�]�զr�¦�I��
#define SHOW_WHOS_TURN_POS ComXY(40,2)       //��ܭ��@��U�Ѫ��y��
#define SHOW_WHAT_YOU_CHOSE_POS ComXY(40, 4) //��ܧA������ӴѤl���y��
#define CHESS_BOARD_X 13           //�ѽL����IX
#define CHESS_BOARD_Y 9           //�ѽL����IY
#define KB_44 44   //Keyboard "<"
#define KB_46 46   //Keyboard ">"
#define MID_X srInfo.srWindow.Right/2
#define MID_Y srInfo.srWindow.Bottom/2

// �ѽL
const char ChessScreenChar[16][16] = {
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@",
	"�@�@�@�@�@�@�@" };

const string ChessScreen[CHESSMAP_SIZE_COLUMN][CHESSMAP_SIZE_ROW] = {};

const char mainMenuScreen[WINDOW_LINES][WINDOW_COLS + 1] = {
	"������������������������������������������",
	"��  888888        88  88        888888  ��",
	"��    88          88  88        88      ��",
	"��    88          888888        88888   ��",
	"��    88          88  88        88      ��",
	"��    88          88  88        888888  ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��   ,o888o, 88  88 88888 ,o88; ,o88;   ��",
	"��   88      88  88 88    '88   '88     ��",
	"��   88      888888 8888    88    88    ��",
	"��   88      88  88 88       88    88   ��",
	"��   '88888' 88  88 88888 `888'  `888'  ��",
	"������������������������������������������" };

const char gameScreen[WINDOW_LINES][WINDOW_COLS + 1] = {
	"������������������������������������������",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"��                                      ��",
	"������������������������������������������" };

const char gameInfoScreen[8][39] = {  //8*39
	"��      �{�b����          �U��      ��",
	"��                                  ��",
	"��                                  ��",
	"��                                  ��",
	"��                                  ��",
	"��                                  ��",
	"��                                  ��",
	"��������������������������������������" };

const char optionInfoScreen[6][39] = {  //6*39
	"��������������������������������������",
	"��   ��                             ��",
	"�� ��  ��  ��V�䱱����           ��",
	"��   ��                             ��",
	"��                                  ��",
	"��  Enter  ����Ѥl       Esc ���  ��", };

const char aboutScreen[WINDOW_LINES][WINDOW_COLS + 1] = {
	"������������������������������������������",
	"���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
	"���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
	"���@�������@�ݢݢ޵{���]�p�@�����M�D�@�@��",
	"���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
	"���@�@�ĤC�ա@�խ��@�@�@�@�@�@�@�@�@�@�@��",
	"��           �@        �@               ��",
	"���@�@�@�@A1045533�@�d�ө��@�@�@�@�@�@�@��",
	"���@�@�@�@A1045535�@���v�l�@�@�@�@�@�@�@��",
	"���@�@�@�@A1045542�@�s��N�@�@�@�@�@�@�@��",
	"��         �@        �@                 ��",
	"��         �@        �@                 ��",
	"��         �@        �@                 ��",
	"���@�������@�ϢפH�u���z�@�@�����M�D�@�@��",
	"��                            �@    �@  ��",
	"���@�@�ĤC�ա@�խ��@�@�@�@�@�@�@�@�@�@�@��",
	"��                            �@    �@  ��",
	"���@�@�@�@A1045533�@�d�ө��@�@�@�@�@�@�@��",
	"���@�@�@�@A1055530�@�����ӡ@�@�@�@�@�@�@��",
	"��                        �@�@          ��",
	"��                                �@�@  ��",
	"��                                �@�@  ��",
	"��                                  �@�@��",
	"������������������������������������������" };

class GUI {
public:
	GUI();
	~GUI();
	short mainMenu();    //  1=start ; 2=setting ; 3=exit
	short MenuInGame();  //  1=resume ; 2=restart ; 3=exit
	void setVisible(bool);
	void dwSize(int);
	//--------------------
	void displayGameScreen(const Map& map, bool isWhosTurn, const Chess *ch = nullptr);
	void displayChessboard(const Map&);
	void displayGameInfo(bool, const Map&, const Chess *ch = nullptr);
	void displayOptionInfo(const Map&);
	//--------------------
	void displayPossiblePath(Chess* ch, const Map& map);
	bool showConfirm(const string&);          //<==�ж��n22�b�Φr��
	void showAlert(const string, const short);//<==�ж��n22�b�Φr��
	void displayExitScreen();
	void displayAboutScreen();
	int displayUpgradeScreen();
	void gotoxy(COORD);
	void gotoxy(short, short);
	void showTextColor(string, SHORT);
	void displayBDeathScreen(const Chess*, int);
	void displayWDeathScreen(const Chess*, int);
private:
	void setColor(INT);
};
#endif