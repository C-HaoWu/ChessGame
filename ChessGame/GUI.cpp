#include "GUI.h"
#include <Windows.h>
#include <conio.h>
#include <fstream>

static CONSOLE_SCREEN_BUFFER_INFO srInfo;
static const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static CONSOLE_CURSOR_INFO crInfo;

GUI::GUI()
{
	system("chcp 950");
	system("mode con: cols=42 lines=24");
	//SetConsoleTitle();
	GetConsoleScreenBufferInfo(hConsole, &srInfo);
	GetConsoleCursorInfo(hConsole, &crInfo);
	if (hConsole == INVALID_HANDLE_VALUE)
		exit(EXIT_FAILURE);
}
GUI::~GUI() {}

void GUI::gotoxy(SHORT x, SHORT y)
{
	COORD hwCursorPosition{ x, y };
	SetConsoleCursorPosition(hConsole, hwCursorPosition);
}
void GUI::gotoxy(COORD cd)
{
	SetConsoleCursorPosition(hConsole, cd);
}

void GUI::setVisible(bool op)
{
	crInfo.bVisible = op;
	SetConsoleCursorInfo(hConsole, &crInfo);
}

void GUI::dwSize(int size)
{
	crInfo.dwSize = size;
	SetConsoleCursorInfo(hConsole, &crInfo);
}

void GUI::showTextColor(std::string word, SHORT color)
{
	SetConsoleTextAttribute(hConsole, color);
	cout << word;
	SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}

void GUI::setColor(INT color)
{
	SetConsoleTextAttribute(hConsole, color);
}

void GUI::displayChessboard(const Map& map)
{
	COORD bufferSize = { 18, 9 };
	COORD characterBufferSize = { 16, 8 };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { CHESS_BOARD_X, CHESS_BOARD_Y, CHESS_BOARD_X + 18 - 1, CHESS_BOARD_Y + 18 - 1 };
	CHAR_INFO consoleBuffer[16 * 16];
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	for (int y = 0; y < (8); ++y) {
		for (int x = 0; x < 16; x++) {
			for (int i = 0; i < 4; i++) {
				consoleBuffer[x + 16 * y].Attributes = (((y % 4 == i && x % 4 == i) || (y % 4 == i && x % 4 == i - 1) || (y % 4 == i - 2 && x % 4 == i) || (y % 4 == i - 2 && x % 4 == i - 1) || (y % 4 == i - 1 && x % 4 == i - 2) || (y % 4 == i - 1 && x % 4 == i - 3) || (y % 4 == i - 3 && x % 4 == i - 3) || (y % 4 == i - 3 && x % 4 == i - 2)) ? WD_WHITE_BG_LGRAY : WD_WHITE_BG_DGRAY);
				consoleBuffer[x + 16 * y].Char.AsciiChar = ChessScreenChar[y][x];
			}

		}
	}
	for (int x = 0; x < ROW_SIZE; x++)
		for (int y = 0; y < COLUMN_SIZE; y++)
			if (map.pChess[x][y] != NULL) {
				consoleBuffer[(x * 2) + 16 * (y)].Attributes = ((map.pChess[x][y]->getColor() == true) ? (((x + y) % 2 == 0) ? WD_BLACK_BG_LGRAY : WD_BLACK_BG_DGRAY) : (((x + y) % 2 == 0) ? WD_WHITE_BG_LGRAY : WD_WHITE_BG_DGRAY));
				consoleBuffer[(x * 2) + 16 * (y)+1].Attributes = ((map.pChess[x][y]->getColor() == true) ? (((x + y) % 2 == 0) ? WD_BLACK_BG_LGRAY : WD_BLACK_BG_DGRAY) : (((x + y) % 2 == 0) ? WD_WHITE_BG_LGRAY : WD_WHITE_BG_DGRAY));
				consoleBuffer[(x * 2) + 16 * (y)].Char.AsciiChar = map.pChess[x][y]->getName().at(0);
				consoleBuffer[(x * 2) + 16 * (y)+1].Char.AsciiChar = map.pChess[x][y]->getName().at(1);
			}
	// Write our character buffer (a single character currently) to the console buffer 
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void GUI::displayGameInfo(bool isWhosTurn, const Map& map, const Chess *ch)
{
	const int cols = 38;
	const int lines = 8;
	COORD bufferSize = { cols, lines };
	COORD characterBufferSize = { cols, lines };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 2, 1, 2 + cols - 1, 1 + lines - 1 };
	CHAR_INFO consoleBuffer[cols * lines];
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	for (int y = 0; y < lines; ++y)
		for (int x = 0; x < cols; ++x) {
			consoleBuffer[x + cols * y].Attributes = DEFAULT_COLOR;
			consoleBuffer[x + cols * y].Char.AsciiChar = gameInfoScreen[y][x];
		}
	for (int y = 0; y < 21; ++y) {
		for (int x = 2; x < 36; ++x) {
			if (y == 0) {   //  ²ִ1¦ז
				consoleBuffer[x + cols * y].Attributes = WD_OCEANBLUE_BG_BLACK;
				if (x >= 18 && x <= 23) {
					consoleBuffer[x + cols * y].Char.AsciiChar = string(isWhosTurn ? "¶ֲ¦ג₪ט" : "¥ױ¦ג₪ט").at(x - 18);
					consoleBuffer[x + cols * y].Attributes = isWhosTurn ? WD_GRAY_BG_BLACK : WD_WHITE_BG_BLACK;
				}
			}
			else if (y == 2 && ch != nullptr) {  //²ִ3¦ז
				consoleBuffer[x + cols * y].Attributes = WD_OCEANBLUE_BG_BLACK;
				if (x >= 12 && x <= 23) {
					consoleBuffer[x + cols * y].Char.AsciiChar = string(string("±z¿ן¾Ü₪F  ") + string(ch->getName())).at(x - 12);
					if (x == 22 || x == 23)
						consoleBuffer[x + cols * y].Attributes = isWhosTurn ? WD_GRAY_BG_BLACK : WD_WHITE_BG_BLACK;
				}
			}
			else if (y == 4 && (map.isChecking(true) || map.isChecking(false))) { //  ²ִ7¦ז		
				if ((isWhosTurn && map.isChecking(true)) || ((!isWhosTurn) && map.isChecking(false))) {
					consoleBuffer[x + cols * 3].Attributes = 68;
					consoleBuffer[x + cols * 4].Attributes = 68;
					consoleBuffer[x + cols * 5].Attributes = 68;
				}
				if (x >= 9 && x <= 28) {
					consoleBuffer[x + cols * y].Attributes = WD_OCEANBLUE_BG_BLACK;
					if (isWhosTurn && map.isChecking(true))
						consoleBuffer[x + cols * y].Char.AsciiChar = string("¡I  ¶ֲ₪ט  ³Q±N­x  ¡I").at(x - 9);
					else if ((!isWhosTurn) && map.isChecking(false))
						consoleBuffer[x + cols * y].Char.AsciiChar = string("¡I  ¥ױ₪ט  ³Q±N­x  ¡I").at(x - 9);
					if (x >= 13 && x <= 16)
						consoleBuffer[x + cols * y].Attributes = isWhosTurn ? WD_GRAY_BG_BLACK : WD_WHITE_BG_BLACK;
				}
			}
		}
	}

	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void GUI::displayOptionInfo(const Map& map)
{
	const int cols = 38;
	const int lines = 6;
	COORD bufferSize = { cols, lines };
	COORD characterBufferSize = { cols, lines };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 2, 17, 2 + cols - 1, 17 + lines - 1 };
	CHAR_INFO consoleBuffer[cols * lines];
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	for (int y = 0; y < lines; ++y)
		for (int x = 0; x < cols; ++x) {
			consoleBuffer[x + cols * y].Attributes = DEFAULT_COLOR;
			consoleBuffer[x + cols * y].Char.AsciiChar = optionInfoScreen[y][x];
		}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

bool GUI::showConfirm(const string& info)
{
	// A COORD struct for specificying the console's screen buffer dimensions 
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };

	// Setting up different variables for passing to WriteConsoleOutput 
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };

	// A CHAR_INFO structure containing data about a single character 
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];

	// Set the screen's buffer size 
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	// Write our character buffer (a single character currently) to the console buffer 
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(false);
	bool point = false;
	setColor(12);
	gotoxy(MID_X - 12, MID_Y - 3);
	cout << "שÝשששששששששששששששששששששששששששששששששששששששששששששß"; gotoxy(MID_X - 12, MID_Y - 2);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y - 1);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y);
	cout << "שר"; showTextColor(info, DEFAULT_COLOR); setColor(12); cout << "שר"; gotoxy(MID_X - 12, MID_Y + 1);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 2);
	cout << "שר     ¬O        §_     שר"; gotoxy(MID_X - 12, MID_Y + 3);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 4);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 5);
	cout << "שדשששששששששששששששששששששששששששששששששששששששששששששו";
	char KB;
	while (true)
	{
		gotoxy(MID_X - 5, MID_Y + 2);
		showTextColor("¬O", !point ? 15 : 240);
		gotoxy(MID_X + 5, MID_Y + 2);
		showTextColor("§_", point ? 15 : 240);
		KB = _getch();
		switch (KB)
		{
		case KB_LEFT:
		case KB_RIGHT:
			point = !point;
			break;
		case KB_ENTER:
			WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
			return point;
			break;
		default:
			break;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	return point;
}


void GUI::displayExitScreen()
{
	HWND hwnd = GetConsoleWindow();
	WINDOWINFO rr;
	GetWindowInfo(hwnd, &rr);
	COORD window{ rr.rcClient.right - rr.rcClient.left, rr.rcClient.bottom - rr.rcClient.top };
	HDC hdc = GetDC(hwnd);
	HDC memhdc = CreateCompatibleDC(hdc);
	HBITMAP cross = CreateCompatibleBitmap(hdc, window.X, window.Y);
	SelectObject(memhdc, cross);
	int x1 = 0;
	int y1 = 0;
	int x2 = window.X;
	int y2 = window.Y;
	int speed = 6;
	int density = 4;
	int color = 200;
	while (1) {
		DeleteObject(cross);
		cross = CreateCompatibleBitmap(hdc, window.X, window.Y);
		SelectObject(memhdc, cross);
		int y = 200;
		for (int x = x1; x < x2; x += density) {
			for (int y = y1; y < y2; y += density) {
				color = rand() % 256 + y1;

				if (color>255)color = 255;
				SetPixel(memhdc, x, y, RGB(color, color, color));
			}
		}
		x1 += 2 * speed, y1 += speed, x2 -= 2 * speed, y2 -= speed;
		BitBlt(hdc, 0, 0, window.X, window.Y, memhdc, 0, 0, SRCCOPY);
		if (x1 >(window.X / 2))break;
		else if (x1 > (window.X / 4)) { density = 2; }
		else if (x1 > (window.X / 3)) { density = 1; }
	}
}

short GUI::mainMenu()
{
	system("cls");
	class printMenu {
	private:
		COORD bufferSize;
		COORD characterBufferSize;
		COORD characterPosition;
		SMALL_RECT consoleWriteArea;
		CHAR_INFO *consoleBuffer;
	public:
		printMenu() {
			consoleBuffer = new CHAR_INFO[WINDOW_COLS * WINDOW_LINES];
			bufferSize = { WINDOW_COLS, WINDOW_LINES };
			characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
			characterPosition = { 0, 0 };
			consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
		}
		void print(int color, int option) {
			char* options[4] = { "ֲש₪H¹Cְ¸", "¡@ֳצ©ף¡@", "°h¥X¹Cְ¸", "¹q¸£¹ן¾װ" };
			SetConsoleScreenBufferSize(hConsole, bufferSize);
			for (int y = 0; y < WINDOW_LINES; ++y) {
				for (int x = 0; x < WINDOW_COLS; ++x) {
					consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = mainMenuScreen[y][x];
					consoleBuffer[x + WINDOW_COLS * y].Attributes = (((y / 2 + x + color) / 20) % 6 + 1);
				}
			}
			for (int y = 9; y <= 15; ++y) {
				if (y % 2 == 0)continue;
				for (int x = 18; x <= 25; ++x) {
					consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = options[(y - 9) / 2][x - 18];
					consoleBuffer[x + WINDOW_COLS * y].Attributes = 7;
					if (((y - 9) / 2) + 1 == option)
						consoleBuffer[x + WINDOW_COLS * y].Attributes = 112;
				}
			}
			WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
		}
		~printMenu() {
			delete[] consoleBuffer;
		}
	};

	printMenu image;
	bool stop = false;
	static int option = 1;
	int const optionsNum = 4;
	std::thread t1([&]() {
		int color = DEFAULT_COLOR;
		while (!stop) {
			image.print(color, option);
			color++;
			if (color > 10000)
				color = DEFAULT_COLOR;
			Sleep(150);
		}
	});
	setVisible(false);
	CHAR Input;
	bool end = false;
	while (!end) {
		Input = _getch();
		setVisible(false);
		switch (Input) {
		case KB_UP:
			if (option != 1)
				option--;
			else
				option = optionsNum;
			break;
		case KB_DOWN:
			if (option != optionsNum)
				option++;
			else
				option = 1;
			break;
		case KB_ENTER:
			end = true;
			stop = true;
			break;
		default:
			break;
		}
	}
	t1.join();
	return option;
}

short GUI::MenuInGame()
{
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	bool decided = false;
	string options[4] = { "ִ~ִע¹Cְ¸", "­«·s¶}©l", "¦^¥D¿ן³ז", "ֲק¶}¹Cְ¸" };
	short option = 1;
	setColor(112);
	gotoxy(MID_X - 8, MID_Y - 5);
	cout << "שÝשששששששששששששששששששששששששששששß "; gotoxy(MID_X - 8, MID_Y - 4);
	cout << "שר              שר ";				 gotoxy(MID_X - 8, MID_Y - 3);
	cout << "שאשששששששששששששששששששששששששששששג "; gotoxy(MID_X - 8, MID_Y - 2);
	cout << "שר              שר ";				 gotoxy(MID_X - 8, MID_Y - 1);
	cout << "שאשששששששששששששששששששששששששששששג "; gotoxy(MID_X - 8, MID_Y);
	cout << "שר              שר ";				 gotoxy(MID_X - 8, MID_Y + 1);
	cout << "שאשששששששששששששששששששששששששששששג "; gotoxy(MID_X - 8, MID_Y + 2);
	cout << "שר              שר ";				 gotoxy(MID_X - 8, MID_Y + 3);
	cout << "שדשששששששששששששששששששששששששששששו ";
	setColor(WD_BLACK_BG_WHITE);
	CHAR Input;
	while (!decided)
	{
		for (int i = 0; i < 4; i++) {
			gotoxy(MID_X - 3, MID_Y - 4 + 2 * i);
			if (option == (i + 1))
				showTextColor(options[i], 7);//₪ֿ¥ױֳC¦ג
			else
				showTextColor(options[i], 112);
		}
		setVisible(false);
		Input = _getch();
		switch (Input)
		{
		case KB_UP:
			if (option != 1)
				option--;
			else
				option = 4;
			break;
		case KB_DOWN:
			if (option != 4)
				option++;
			else
				option = 1;
			break;
		case KB_ENTER:
			decided = true;
			break;
		case KB_ESC:
			option = 1;
			decided = true;
		default:
			break;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	return option;
}

void GUI::displayPossiblePath(Chess* ch, const Map& map)
{
	COORD bufferSize = { 18, 9 };
	COORD characterBufferSize = { 16, 8 };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { CHESS_BOARD_X, CHESS_BOARD_Y, CHESS_BOARD_X + 18 - 1, CHESS_BOARD_Y + 18 - 1 };
	CHAR_INFO consoleBuffer[16 * 16];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	for (int y = 0; y < (8); ++y) {
		for (int x = 0; x < 16; x++) {
			for (int i = 0; i < 4; i++) {
				consoleBuffer[x + 16 * y].Attributes = (((y % 4 == i && x % 4 == i) || (y % 4 == i && x % 4 == i - 1) || (y % 4 == i - 2 && x % 4 == i) || (y % 4 == i - 2 && x % 4 == i - 1) || (y % 4 == i - 1 && x % 4 == i - 2) || (y % 4 == i - 1 && x % 4 == i - 3) || (y % 4 == i - 3 && x % 4 == i - 3) || (y % 4 == i - 3 && x % 4 == i - 2)) ? WD_WHITE_BG_LGRAY : WD_WHITE_BG_DGRAY);
				consoleBuffer[x + 16 * y].Char.AsciiChar = ChessScreenChar[y][x];
			}

		}
	}
	for (int x = 0; x < ROW_SIZE; x++)
		for (int y = 0; y < COLUMN_SIZE; y++)
			if (map.pChess[x][y] != NULL) {
				consoleBuffer[(x * 2) + 16 * (y)].Attributes = ((map.pChess[x][y]->getColor() == true) ? (((x + y) % 2 == 0) ? WD_BLACK_BG_LGRAY : WD_BLACK_BG_DGRAY) : (((x + y) % 2 == 0) ? WD_WHITE_BG_LGRAY : WD_WHITE_BG_DGRAY));
				consoleBuffer[(x * 2) + 16 * (y)+1].Attributes = ((map.pChess[x][y]->getColor() == true) ? (((x + y) % 2 == 0) ? WD_BLACK_BG_LGRAY : WD_BLACK_BG_DGRAY) : (((x + y) % 2 == 0) ? WD_WHITE_BG_LGRAY : WD_WHITE_BG_DGRAY));
				consoleBuffer[(x * 2) + 16 * (y)].Char.AsciiChar = map.pChess[x][y]->getName().at(0);
				consoleBuffer[(x * 2) + 16 * (y)+1].Char.AsciiChar = map.pChess[x][y]->getName().at(1);
			}
	for (SHORT i = 0; i < ROW_SIZE; i++)
		for (SHORT j = 0; j < COLUMN_SIZE; j++) {
			if (ch->isValid(COORD{ i,j }, map)) {
				Chess *tempch = map.pChess[i][j];
				consoleBuffer[(i * 2) + 16 * j].Attributes = (tempch == NULL ? 230 : (tempch->getColor() ? 60 : 48));
				consoleBuffer[(i * 2) + 16 * j + 1].Attributes = (tempch == NULL ? 230 : (tempch->getColor() ? 60 : 48));
				if (tempch != NULL) {
					consoleBuffer[(i * 2) + 16 * j].Char.AsciiChar = tempch->getName().at(0);
					consoleBuffer[(i * 2) + 16 * j + 1].Char.AsciiChar = tempch->getName().at(1);
				}
			}
			if (ch->isCastling(COORD{ i,j }, map)) {
				Chess *tempch = map.pChess[i][j];
				consoleBuffer[(i * 2) + 16 * j].Attributes = (tempch->getColor() ? 60 : 48);
				consoleBuffer[(i * 2) + 16 * j + 1].Attributes = (tempch->getColor() ? 60 : 48);
				if (tempch != NULL) {
					consoleBuffer[(i * 2) + 16 * j].Char.AsciiChar = tempch->getName().at(0);
					consoleBuffer[(i * 2) + 16 * j + 1].Char.AsciiChar = tempch->getName().at(1);
				}
			}
		}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void GUI::showAlert(const string info, const short time)
{
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);

	setVisible(false);
	setColor(12);
	gotoxy(MID_X - 12, MID_Y - 3);
	cout << "שÝשששששששששששששששששששששששששששששששששששששששששששששß"; gotoxy(MID_X - 12, MID_Y - 2);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y - 1);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 1);
	cout << "שר"; showTextColor(info, DEFAULT_COLOR); setColor(12); cout << "שר"; gotoxy(MID_X - 12, MID_Y + 2);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 3);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 4);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 5);
	cout << "שדשששששששששששששששששששששששששששששששששששששששששששששו";
	setColor(DEFAULT_COLOR);
	Sleep(time);
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	setVisible(true);
}

void GUI::displayGameScreen(const Map& map, bool isWhosTurn, const Chess* ch)
{
	COORD bufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition{ 0, 0 };
	SMALL_RECT consoleWriteArea{ 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	for (int y = 0; y < WINDOW_LINES; ++y) {
		for (int x = 0; x < WINDOW_COLS; ++x) {
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = gameScreen[y][x];
			consoleBuffer[x + WINDOW_COLS * y].Attributes = DEFAULT_COLOR;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	displayChessboard(map);
	displayGameInfo(isWhosTurn, map, ch);
	displayOptionInfo(map);
}

void GUI::displayAboutScreen()
{
	COORD bufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize{ WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition{ 0, 0 };
	SMALL_RECT consoleWriteArea{ 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	for (int y = 0; y < WINDOW_LINES; ++y) {
		for (int x = 0; x < WINDOW_COLS; ++x) {
			consoleBuffer[x + WINDOW_COLS * y].Char.AsciiChar = aboutScreen[y][x];
			consoleBuffer[x + WINDOW_COLS * y].Attributes = DEFAULT_COLOR;
		}
	}
	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	_getch();
}

void GUI::displayBDeathScreen(const Chess*ch, int i)
{
	gotoxy(10 - 2 * (i % 4), 16 - (i / 4));
	cout << ch->getName();
}

void GUI::displayWDeathScreen(const Chess*ch, int j)
{
	gotoxy(30 + 2 * (j % 4), 9 + (j / 4));
	cout << ch->getName();
}

int GUI::displayUpgradeScreen()
{
	COORD bufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterBufferSize = { WINDOW_COLS, WINDOW_LINES };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_COLS - 1, WINDOW_LINES - 1 };
	CHAR_INFO consoleBuffer[WINDOW_COLS * WINDOW_LINES];
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	ReadConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	bool decided = false;
	string options[4] = { "¬׃¦Z", "ֳM₪h", "«°³ש","¥D±׀" };
	short option = 1;
	setVisible(true);
	setColor(12);
	gotoxy(MID_X - 12, MID_Y - 5);
	cout << "שÝשששששששששששששששששששששששששששששששששששששששששששששß"; gotoxy(MID_X - 12, MID_Y - 4);
	cout << "שר"; showTextColor("¡@½׀¿ן¾Ü­n₪ֹ¯ֵ×÷´ׁ₪l¡@", DEFAULT_COLOR); setColor(12); cout << "שר"; gotoxy(MID_X - 12, MID_Y - 3);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y - 2);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y - 1);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 1);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 2);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 3);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 4);
	cout << "שר                      שר"; gotoxy(MID_X - 12, MID_Y + 5);
	cout << "שדשששששששששששששששששששששששששששששששששששששששששששששו";
	setColor(DEFAULT_COLOR); CHAR Input;
	while (!decided)
	{
		for (int i = 0; i < 4; i++) {
			gotoxy(MID_X - 1, MID_Y - 2 + 2 * i);
			if (option == (i + 1))
				showTextColor(options[i], 112);//₪ֿ¥ױֳC¦ג
			else
				showTextColor(options[i], DEFAULT_COLOR);
		}
		setVisible(false);
		Input = _getch();
		switch (Input)
		{
		case KB_UP:
			if (option != 1)
				option--;
			else
				option = 4;
			break;
		case KB_DOWN:
			if (option != 4)
				option++;
			else
				option = 1;
			break;
		case KB_ENTER:
			decided = true;
			break;
		case KB_ESC:
			option = 1;
			decided = true;
		default:
			break;
		}
	}

	WriteConsoleOutputA(hConsole, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
	return option;
}