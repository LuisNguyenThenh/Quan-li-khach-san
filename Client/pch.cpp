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
	accountLogin();
	
	fstream out;
	out.open("Text.txt", ios::app);
	out << this->clientA.username << ' ' << this->clientA.strpass << endl;
	out.close();
}

// phan nay cua server lam nham qua client :)
//bool client::loginValid(string strA, string strB) {
//	user s[3];
//	s[0].username = "thanh";
//	s[1].username = "phuoc";
//	s[2].username = "thai";
//	s[0].strpass = "thanh123";
//	s[1].strpass = "thanh123";
//	s[2].strpass = "thanh123";
//	for (int i = 0; i < 3; i++) {
//		if (strA == s[i].username) {
//			for (int j = 0; j < strB.length(); j++) {
//				if (s[i].strpass[j] != strB[j])
//					return 0;
//			}
//			return 1;
//		}
//	}
//	return 0;
//}

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

void accountRegister(user& clientA, CSocket& clientsocket) {
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
	int p = clientA.username.length(),
		q = clientA.strpass.length();
	clientsocket.Send((char*)&p, sizeof(int), 0);
	clientsocket.Send(&clientA.username, sizeof(p), 0);
	clientsocket.Send((char*)&q, sizeof(int), 0);
	clientsocket.Send(&clientA.strpass, sizeof(q), 0);
}

void client::accountLogin() {
	// neu da co tien hanh dang nhap
	system("cls");
	cout << "Username: ";
	conSole.gotoxy(0, 1);
	cout << "Password: ";
	conSole.gotoxy(10, 0);
	char c;
	int i = 0;
	cin >> this->clientA.username;
	do {
		c = _getch();
		this->clientA.strpass[i] = c;
		conSole.gotoxy(10 + i, 1); cout << "*";
		if (c == 23) {
			this->clientA.strpass[i] = '\0';
			break;
		}
		i++;
	} while (c != 23);
}

