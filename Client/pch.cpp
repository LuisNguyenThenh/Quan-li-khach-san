// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"
#include "framework.h"
// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

consoleGraphic::consoleGraphic() {
	resizeConsole();
	FixConsoleWindow();
}

void consoleGraphic::FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void consoleGraphic::resizeConsole() {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, this->width, this->heigth, TRUE);
}

void consoleGraphic::gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x , y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void consoleGraphic::ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

client::client() {
	return;
}

bool client::registerValid(user clientA) {
	if (strlen(clientA.username) < 5) {
		this->conSole.gotoxy(35, 17); std::cout << "Username is not valid. Try another one";
		return 0;
	}
	if (strlen(clientA.strpass) < 3) {
		this->conSole.gotoxy(35, 17); std::cout << "Password is not valid. Try another one";
		return 0;
	}
	if (strlen(clientA.idBanking) != 10) {
		cout << strlen(clientA.idBanking) << endl;
		this->conSole.gotoxy(35, 17); std::cout << "ID banking is not valid. Try another one";
		return 0;
	}

	for (int i = 0; i < strlen(clientA.username); i++) {
		if ((clientA.username[i] < '0' || clientA.username[i] > '9') && (clientA.username[i] < 'a' || clientA.username[i] > 'z'))
			return 0;
	}
	for (int i = 0; i < strlen(clientA.idBanking); i++) {
		if (clientA.idBanking[i] < '0' || clientA.idBanking[i] > '9')
			return 0;
	}
	return 1;
}

void backspaceKey(char*& str) {
	if (str[0] == '\0')
		return;
	str[strlen(str) - 1] = '\0';
}

void client::accountLogin() {
	// neu da co tien hanh dang nhap
	system("cls");
	this->conSole.gotoxy(35, 7);
	std::cout << "+--------------------------------------------+";
	this->conSole.gotoxy(35, 8);
	std::cout << "|                  Log in                    |";
	this->conSole.gotoxy(35, 9);
	std::cout << "+--------------------------------------------+";
	this->conSole.gotoxy(35, 10);
	std::cout << "| Username:                                  |";
	this->conSole.gotoxy(35, 11);
	std::cout << "| Password:                                  |";
	this->conSole.gotoxy(35, 12);
	std::cout << "+--------------------------------------------+";
	conSole.gotoxy(47, 10);
	cin.getline(clientA.username, 100);
	char c;
	int i = 0;
	int cnt = 0;
	do {
		int h = i + 47;
		if (h < 47)
			h = 47;
		c = _getch();
		if (c == 13) {
			clientA.strpass[cnt] = '\0';
			break;
		}
		if (c == 8) {
			backspaceKey(clientA.strpass);
			conSole.gotoxy(h - 1, 11);
			std::cout << ' ';
			conSole.gotoxy(h - 1, 11);
			cnt--;
			i--;
		}
		else {
			conSole.gotoxy(h, 11);
			std::cout << '*';
			clientA.strpass[cnt] = c;
			i++; cnt++;
		}
	} while (1);
	return;
}
