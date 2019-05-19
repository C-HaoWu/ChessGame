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
#define KB_UP 72     //ֱה½L¿י₪J¼ֶ­ָ ₪W
#define KB_DOWN 80   //ֱה½L¿י₪J¼ֶ­ָ ₪U
#define KB_LEFT 75   //ֱה½L¿י₪J¼ֶ­ָ ¥×
#define KB_RIGHT 77  //ֱה½L¿י₪J¼ֶ­ָ ¥k
#define KB_ENTER 13  //ֱה½L¿י₪J¼ֶ­ָ Enter
#define KB_ESC 27    //ֱה½L¿י₪J¼ֶ­ָ ESC
#define CHESSMAP_SIZE_ROW 16      //´ׁ½LROW    SIZE
#define CHESSMAP_SIZE_COLUMN 8   //´ׁ½Lcolumn SIZE
#define WD_BLACK_BG_WHITE 240     //¶ֲ¦r¥ױ¦ג­I´÷
#define WD_RED_BG_WHITE 252       //¬ץ¦r¥ױ¦ג­I´÷
#define WD_WHITE_BG_LGRAY 127     //¥ױ®ז¥ױ´ׁ ((«G¦ַ©³¥ױ¦r
#define WD_BLACK_BG_LGRAY 112     //¥ױ®ז¶ֲ´ׁ ((«G¦ַ©³¶ֲ¦r
#define WD_WHITE_BG_DGRAY 143     //¶ֲ®ז¥ױ´ׁ ((·t¦ַ©³¥ױ¦r
#define WD_BLACK_BG_DGRAY 128     //¶ֲ®ז¶ֲ´ׁ ((·t¦ַ©³¶ֲ¦r
#define WD_RED_BG_BLACK 12        //¬ץ¦r¶ֲ¦ג­I´÷
#define WD_WHITE_BG_BLACK 15       //¥ױ¦r¶ֲ¦ג­I´÷
#define WD_OCEANBLUE_BG_BLACK 11  //₪פֲֵ¦ג¦r¶ֲ¦ג­I´÷
#define WD_GRAY_BG_BLACK 8        //¦ַ¦ג¦r¶ֲ¦ג­I´÷
#define DEFAULT_COLOR 7           //¹w³]¥ױ¦r¶ֲ¦ג­I´÷
#define SHOW_WHOS_TURN_POS ComXY(40,2)       //ֵד¥Ü­‏₪@₪ט₪U´ׁ×÷®y¼׀
#define SHOW_WHAT_YOU_CHOSE_POS ComXY(40, 4) //ֵד¥Ü§A¿ן¨ת­‏­׃´ׁ₪l×÷®y¼׀
#define CHESS_BOARD_X 13           //´ׁ½L°ע·ֲַIX
#define CHESS_BOARD_Y 9           //´ׁ½L°ע·ֲַIY
#define KB_44 44   //Keyboard "<"
#define KB_46 46   //Keyboard ">"
#define MID_X srInfo.srWindow.Right/2
#define MID_Y srInfo.srWindow.Bottom/2

// ´ׁ½L
const char ChessScreenChar[16][16] = {
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@",
	"¡@¡@¡@¡@¡@¡@¡@" };

const string ChessScreen[CHESSMAP_SIZE_COLUMN][CHESSMAP_SIZE_ROW] = {};

const char mainMenuScreen[WINDOW_LINES][WINDOW_COLS + 1] = {
	"שÝשששששששששששששששששששששששששששששששששששששששß",
	"שר  888888        88  88        888888  שר",
	"שר    88          88  88        88      שר",
	"שר    88          888888        88888   שר",
	"שר    88          88  88        88      שר",
	"שר    88          88  88        888888  שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר   ,o888o, 88  88 88888 ,o88; ,o88;   שר",
	"שר   88      88  88 88    '88   '88     שר",
	"שר   88      888888 8888    88    88    שר",
	"שר   88      88  88 88       88    88   שר",
	"שר   '88888' 88  88 88888 `888'  `888'  שר",
	"שדשששששששששששששששששששששששששששששששששששששששו" };

const char gameScreen[WINDOW_LINES][WINDOW_COLS + 1] = {
	"שÝשÞשששששששששששששששששששששששששששששששששששÞשß",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שר                                      שר",
	"שדשהשששששששששששששששששששששששששששששששששששהשו" };

const char gameInfoScreen[8][39] = {  //8*39
	"שר      ²{¦b½ü¨ל          ₪U´ׁ      שר",
	"שר                                  שר",
	"שר                                  שר",
	"שר                                  שר",
	"שר                                  שר",
	"שר                                  שר",
	"שר                                  שר",
	"שדשששששששששששששששששששששששששששששששששששו" };

const char optionInfoScreen[6][39] = {  //6*39
	"שÝשששששששששששששששששששששששששששששששששששß",
	"שר   ¡פ                             שר",
	"שר ¡צ  ¡ק  ₪ט¦Vֱה±±¨מ´ו¼׀           שר",
	"שר   ¡ץ                             שר",
	"שר                                  שר",
	"שר  Enter  ¿ן¨ת´ׁ₪l       Esc ¿ן³ז  שר", };

const char aboutScreen[WINDOW_LINES][WINDOW_COLS + 1] = {
	"שÝשששששששששששששששששששששששששששששששששששששששß",
	"שר¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@שר",
	"שר¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@שר",
	"שר¡@¢°¢¯¢´¡@¢Ý¢Ý¢Þµ{¦¡³]­p¡@´ֱ¥½±MֳD¡@¡@שר",
	"שר¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@שר",
	"שר¡@¡@²ִ₪C²ױ¡@²ױ­û¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@שר",
	"שר           ¡@        ¡@               שר",
	"שר¡@¡@¡@¡@A1045533¡@§d©׃©‏¡@¡@¡@¡@¡@¡@¡@שר",
	"שר¡@¡@¡@¡@A1045535¡@ֱ§ֳvגl¡@¡@¡@¡@¡@¡@¡@שר",
	"שר¡@¡@¡@¡@A1045542¡@ְs±ך×N¡@¡@¡@¡@¡@¡@¡@שר",
	"שר         ¡@        ¡@                 שר",
	"שר         ¡@        ¡@                 שר",
	"שר         ¡@        ¡@                 שר",
	"שר¡@¢°¢¯¢¶¡@¢ֿ¢׳₪H₪u´¼¼z¡@¡@´ֱ¥½±MֳD¡@¡@שר",
	"שר                            ¡@    ¡@  שר",
	"שר¡@¡@²ִ₪C²ױ¡@²ױ­û¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@שר",
	"שר                            ¡@    ¡@  שר",
	"שר¡@¡@¡@¡@A1045533¡@§d©׃©‏¡@¡@¡@¡@¡@¡@¡@שר",
	"שר¡@¡@¡@¡@A1055530¡@§ץ«ֵו׃¡@¡@¡@¡@¡@¡@¡@שר",
	"שר                        ¡@¡@          שר",
	"שר                                ¡@¡@  שר",
	"שר                                ¡@¡@  שר",
	"שר                                  ¡@¡@שר",
	"שדשששששששששששששששששששששששששששששששששששששששו" };

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
	bool showConfirm(const string&);          //<==½׀¶ס­ט¦n22¥b§־¦r₪¸
	void showAlert(const string, const short);//<==½׀¶ס­ט¦n22¥b§־¦r₪¸
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