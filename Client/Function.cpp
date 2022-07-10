#include <conio.h>
#include "framework.h"
#include "pch.h"

// Request 4
void booking(CSocket& connector, char* username)
{
	// Choose hotel

	int size_username = strlen(username);
	// Gui username cho server
	connector.Send((char*)&size_username, sizeof(int), 0);
	connector.Send((char*)username, size_username, 0);

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
	} while (name_hotel_exist == false);

	
	//int number_of_room_remaining;
	//// Nhận từ server số phòng còn trống.
	//connector.Receive((char*)&number_of_room_remaining, sizeof(int), 0);
	// Số lượng phòng muốn đặt 
	int number_of_room_booking;
	cout << "Number of room you want to book: ";
	cin >> number_of_room_booking;

	//// Kiểm tra số lượng phòng cần đặt có vượt quá số phòng đang có hay ko?
	//while (number_of_room_booking > number_of_room_remaining)
	//{
	//	cout << "Sorry we don't have enough room available for you right now! Please try again:";
	//	cin >> number_of_room_booking;
	//}

	// Choose kind of room		
// Gửi đi số phòng cần đặt
	connector.Send((char*)&number_of_room_booking, sizeof(int), 0);

	// Xử lý các phòng.
	for (int i = 0; i < number_of_room_booking; i++)
	{
		cout << "Room " << i + 1 << endl;
		cout << "Choose the number correspond to kind of room in this " << name_hotel << endl;

		cout << "1. Standard Room." << endl;
		cout << "2. Superior Room." << endl;
		cout << "3. Deluxe Room." << endl; 
		cout << "4. Suite Room." << endl;

		
		//char* content_kinds_of_room = new char[500];
		//int sz_content_kinds_of_room;

		//// Nhận bảng thông tin từ server với các chi tiết cụ thể về từng loại phòng.
		//connector.Receive((char*)&sz_content_kinds_of_room, sizeof(int), 0);
		//connector.Receive(content_kinds_of_room, sz_content_kinds_of_room, 0);
		//content_kinds_of_room[sz_content_kinds_of_room + 1] = '\0';

		//// Xuất bảng thông tin nhận từ server
		//cout << content_kinds_of_room << endl;

		int option_of_client;
		bool kind_of_this_room_exist;

		cout << "The kind of room you want to choose is:";
		cin >> option_of_client;

		// Gửi loại phòng cần chọn cho server.
		connector.Send((char*)&option_of_client, sizeof(int), 0);
		do
		{

			//  Ngày vào ở 
			date date_in,date_out;
			bool check_invaild_date;
			char c;
			do
			{
				cout << "Date of entry: ";
				cin >> date_in.d >> c >> date_in.m >> c >> date_in.y;

				// Ngày đi 

				cout << "Date leaving: ";
				cin >> date_out.d >> c >> date_out.m >> c >> date_out.y;

				check_invaild_date = (kiem_tra_ngay_thang_nam(date_in) == false) | (kiem_tra_ngay_thang_nam(date_out) == false) | (date_larger_than(date_out, date_in) < 0);
				if (check_invaild_date)
				{
					cout << "Error date! Please try again:";
				}

			} while (check_invaild_date);
			
			connector.Send((char*)&date_in, sizeof(date), 0);

			connector.Send((char*)&date_out, sizeof(date), 0);

			// Chọn loại phòng dựa vào số thứ tự trong bảng thông tin


			//Nhận thông báo từ server để xem loại phòng này có không?
			connector.Receive((char*)&kind_of_this_room_exist, sizeof(bool), 0);
			if (kind_of_this_room_exist == false)
			{
				cout << "Sorry we don't have this kind of room! " << endl;
				cout << "Please try anothers date!" << endl;
			}
		} while (kind_of_this_room_exist == false);

		// Note
		char* note = new char[200];
		int size_note;
		cout << "If you have any note please write here: ";
		cin.getline(note, 200);
		size_note = strlen(note);
		connector.Send((char*)&size_note, sizeof(int), 0);
		connector.Send(note, strlen(note), 0);
		delete[] note;
	}
	
	delete[] name_hotel;
	//getchar();
	// Hoa don
	cout << "-Invoice of client!";
	int total_money;
	connector.Receive((char*)&total_money, sizeof(int), 0);
	cout << "Total: " << total_money << " USD" << endl;

	return;
}





void lookup(CSocket& connector) {
	cout << "+-------------------------+\n";
	cout << "|       INFORMATION       |\n";
	cout << "+-------------------------+\n";
	cout << "| 1. Hotel                |\n";
	cout << "| 2. Booking information  |\n";
	cout << "+-------------------------+\n";
	char c = _getch();
	int flag = 1;
	if (c == '1') {
		connector.Send((char*)&flag, sizeof(int), 0);
	}
	if (c == '2') {
		flag = 0;
		connector.Send((char*)&flag, sizeof(int), 0);
	}
	return;
}

void menuClient(CSocket& connector) {
	cout << "+---------------------+\n";
	cout << "|         MENU        |\n";
	cout << "+---------------------+\n";
	cout << "| 1. Lookup           |\n";
	cout << "| 2. Preservation     |\n";
	cout << "+---------------------+\n";

	char c = _getch();
	int flag = 1;
	if (c == '1') {
		connector.Send((char*)&flag, sizeof(int), 0);
	}
	if (c == '2') {
		connector.Send((char*)&flag, sizeof(int), 0);
	}
}