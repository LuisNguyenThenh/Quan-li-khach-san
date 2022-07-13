// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"
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
	accountLogin();
	fstream out;
	out.open("Text.txt", ios::app);
	out << this->clientA.username << ' ' << this->clientA.strpass << endl;
	out.close();
}

bool client::registerValid(user clientA) {
	if (clientA.username.length() < 5 || clientA.strpass.length() < 3 || clientA.idBanking.length() != 10)
		return 0;
	for (int i = 0; i < clientA.username.length(); i++) {
		if ((clientA.username[i] < '0' || clientA.username[i] > '9') && (clientA.username[i] < 'a' || clientA.username[i] > 'z'))
			return 0;
	}
	for (int i = 0; i < clientA.idBanking.length(); i++) {
		if (clientA.idBanking[i] < '0' || clientA.idBanking[i] > '9')
			return 0;
	}
	return 1;
}

void accountRegister(user& clientA) {
	client a;
	do {
		cout << "Username: "; a.conSole.gotoxy(30, 0); cout << "(Username is \'0\' to \'9\' and \'a\' to \'z\')\n";
		cout << "Password: ";
		a.conSole.gotoxy(0, 2); cout << "ID Banking: ";
		a.conSole.gotoxy(10, 0);
		cin >> clientA.username;
		a.conSole.gotoxy(10, 1);
		cin >> clientA.strpass;
		a.conSole.gotoxy(12, 2);
		cin >> clientA.idBanking;
		if (a.registerValid(clientA) == 0) {
			a.conSole.gotoxy(0, 4); cout << "Username or password is not valid. Please try another one.\n";
			system("pause");
			system("cls");
		}
	} while (a.registerValid(clientA) == 0);
}

void client::accountLogin() {
	// neu da co tien hanh dang nhap
	system("cls");
	cout << "Username: ";
	conSole.gotoxy(0, 1);
	cout << "Password: ";
	conSole.gotoxy(10, 0);
	cin >> clientA.username;
	conSole.gotoxy(10, 1);
	cin >> clientA.strpass;
}

void menu(char& c) {
	cout << "+------------------------------------+\n";
	cout << "|                MENU                |\n";
	cout << "+------------------------------------+\n";
	cout << "| 1. Login                           |\n";
	cout << "| 2. Register                        |\n";
	cout << "| 3. Look up                         |\n";
	cout << "| 4. Reservation                     |\n";
	cout << "| 5. Exit                            |\n";
	cout << "+------------------------------------+\n";
	do {
		c = _getch();
		if (c == '1') {
			int k = 1;
			clientsocket.Send((char*)&k, sizeof(int), 0);
		}
		if (c == '2') {
			int k = 0;
			clientsocket.Send((char*)&k, sizeof(int), 0);
		}
		if (c == '3') {
			int k = 2;
			clientsocket.Send((char*)&k, sizeof(int), 0);
		}
		if (c == '4') {
			int k = 3;
			clientsocket.Send((char*)&k, sizeof(int), 0);
		}
	} while (c < '1' || c > '4');
	
}