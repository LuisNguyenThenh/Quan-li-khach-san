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

	/*for (int i = 0;; i++) {
		cin >> strPassword[i];
		conSole.gotoxy(9 + i, 1);
		cout << "*";
		if (strPassword[i] == '\n') {
			strPassword[i] = '\0';
			break;
		}
	}*/
	/*if (loginValid(clientA))
		cout << "valid!";
	else
		cout << "Username or Password doesn't correct.\n";*/
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

bool client::loginValid(user clientA) {
	return 1;
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

// Request 4
void booking(CSocket& connector)
{
	// Choose hotel
	bool name_hotel_exist;
	char* name_hotel = new char[100];
	int size_of_name_hotel;
	bool is_hotel_available;

	cout << "Name of hotel:";
	do
	{
		cin.getline(name_hotel, 100);
		size_of_name_hotel = strlen(name_hotel);

		// Gui ten khach san di
		connector.Send((char*)&size_of_name_hotel, sizeof(int), 0);
		connector.Send(name_hotel, size_of_name_hotel, 0);
		
		//Nhận thông báo từ server để xem tên khách sạn có hợp lên ko?
		connector.Receive((char*)&name_hotel_exist, sizeof(bool), 0);
		if (name_hotel_exist == false)
		{
			cout << "Sorry we don't have this hotel! Please try again:";
		}
		else
		{
			//Nhận thông báo từ server để xem  khách sạn còn phòng hay ko?
			connector.Receive((char*)&is_hotel_available, sizeof(int), 0);
			if (is_hotel_available == false)
			{
				cout << "Sorry this hotel is full now! Please try others:";
			}
		}
	} while (name_hotel_exist == false || is_hotel_available == false);

	// Số lượng phòng muốn đặt 
	int number_of_room_remaining;
	// Nhận từ server số phòng còn trống.
	connector.Receive((char*)&number_of_room_remaining, sizeof(int), 0);

	int number_of_room_booking;
	cout << "Number of room you want to book: ";
	cin >> number_of_room_booking;

	// Kiểm tra số lượng phòng cần đặt có vượt quá số phòng đang có hay ko?
	while (number_of_room_booking > number_of_room_remaining)
	{
		cout << "Sorry we don't have enough room available for you right now! Please try again:";
		cin >> number_of_room_booking;
	}

		// Choose kind of room		
	// Gửi đi số phòng cần đặt
	connector.Send((char*)&number_of_room_booking, sizeof(int), 0);

	// Xử lý các phòng.
	for (int i = 0; i < number_of_room_booking; i++)
	{
		cout << "Room " << i + 1 << endl;
		cout << "Choose the number correspond to kind of room in this " << name_hotel << endl;

		char* content_kinds_of_room = new char[500];
		int sz_content_kinds_of_room;

		// Nhận bảng thông tin từ server với các chi tiết cụ thể về từng loại phòng.
		connector.Receive((char*)&sz_content_kinds_of_room, sizeof(int), 0);
		connector.Receive(content_kinds_of_room, sz_content_kinds_of_room, 0);
		content_kinds_of_room[sz_content_kinds_of_room + 1] = '\0';

		// Xuất bảng thông tin nhận từ server
		cout << content_kinds_of_room << endl;

		int option_of_client;
		bool kind_of_this_room_exist;

		cout << "The kind of room you want to choose is:";
		do
		{
			// Chọn loại phòng dựa vào số thứ tự trong bảng thông tin
			cin >> option_of_client;

			// Gửi loại phòng cần chọn cho server.
			connector.Send((char*)&option_of_client, sizeof(int), 0);

			//Nhận thông báo từ server để xem loại phòng này có không?
			connector.Receive((char*)&kind_of_this_room_exist, sizeof(bool), 0);
			if (kind_of_this_room_exist == false)
			{
				cout << "Sorry we don't have this kind of room! Please try again:";
			}
		} while (kind_of_this_room_exist == false);

		//  Ngày vào ở 
		int day_in, month_in, year_in;
		char c;
		cout << "Date of entry: ";
		cin >> day_in >> c >> month_in >> c >> year_in;

		connector.Send((char*)&day_in, sizeof(int), 0);
		connector.Send((char*)&month_in, sizeof(int), 0);
		connector.Send((char*)&year_in, sizeof(int), 0);

		// Ngày đi 
		int day_out, month_out, year_out;
		cout << "Date leaving: ";
		cin >> day_out >> c >> month_out >> c >> year_out;

		connector.Send((char*)&day_out, sizeof(int), 0);
		connector.Send((char*)&month_out, sizeof(int), 0);
		connector.Send((char*)&year_out, sizeof(int), 0);
	}
	// Note
	char* note = new char[200];
	int size_note;
	cout << "If you have any note please write here: ";
	cin.getline(note, 200);
	size_note = strlen(note);
	connector.Send((char*)&size_note, sizeof(int), 0);
	connector.Send(note, strlen(note), 0);
	//getchar();
	// Hoa don
	cout << "-Invoice of client!";
	int total_money;
	connector.Receive((char*)&total_money, sizeof(int), 0);
	cout << "Total: " << total_money << " USD" << endl;
	
	return;
}

