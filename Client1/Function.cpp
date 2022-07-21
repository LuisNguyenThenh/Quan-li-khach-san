#include <conio.h>
#include "framework.h"
#include "pch.h"

// Request 4
void booking(int connector)
{
	// Choose hotel
	int size_username = strlen(clientA.username);
	// Gui username cho server
	send(connector, (char*)&size_username, sizeof(int), 0);
	send(connector, (char*)clientA.username, size_username, 0);

	bool name_hotel_exist;
	char* name_hotel = new char[100];
	int size_of_name_hotel;
	bool is_hotel_available;


	//Getchar()
	//getchar();

	std::cout << "Name of hotel:";
	do
	{
		cin.getline(name_hotel, 100);
		size_of_name_hotel = strlen(name_hotel);

		// Gui ten khach san di
		send(connector, (char*)&size_of_name_hotel, sizeof(int), 0);
		send(connector, (char*)name_hotel, size_of_name_hotel, 0);

		//Nhận thông báo từ server để xem tên khách sạn có hợp lê ko?
		recv(connector, (char*)&name_hotel_exist, sizeof(bool), 0);
		if (name_hotel_exist == false)
		{
			std::cout << "Sorry we don't have this hotel! Please try again:";
		}
	} while (name_hotel_exist == false);


	//int number_of_room_remaining;
	//// Nhận từ server số phòng còn trống.
	//recv(connector,(char*)&number_of_room_remaining, sizeof(int), 0);
	// Số lượng phòng muốn đặt 
	int number_of_room_booking;
	std::cout << "Number of room you want to book: ";
	cin >> number_of_room_booking;

	//// Kiểm tra số lượng phòng cần đặt có vượt quá số phòng đang có hay ko?
	//while (number_of_room_booking > number_of_room_remaining)
	//{
	//	std::cout << "Sorry we don't have enough room available for you right now! Please try again:";
	//	cin >> number_of_room_booking;
	//}

	// Choose kind of room		
// Gửi đi số phòng cần đặt
	send(connector, (char*)&number_of_room_booking, sizeof(int), 0);

	// Xử lý các phòng.
	for (int i = 0; i < number_of_room_booking; i++)
	{
		std::cout << "Room " << i + 1 << std::endl;
		std::cout << "Choose the number correspond to kind of room in this " << name_hotel << std::endl;

		std::cout << "1. Standard Room." << std::endl;
		std::cout << "2. Superior Room." << std::endl;
		std::cout << "3. Deluxe Room." << std::endl;
		std::cout << "4. Suite Room." << std::endl;

		int option_of_client;
		bool kind_of_this_room_exist;

		std::cout << "The kind of room you want to choose is:";
		cin >> option_of_client;

		// Gửi loại phòng cần chọn cho server.
		send(connector, (char*)&option_of_client, sizeof(int), 0);
		do
		{

			//  Ngày vào ở 
			date date_in, date_out;
			bool check_invaild_date;
			char c;
			do
			{
				std::cout << "Date of entry: ";
				cin >> date_in.d >> c >> date_in.m >> c >> date_in.y;
				std::cout << date_in.d << " " << date_in.m << " " << date_in.y << std::endl;
				// Ngày đi 

				std::cout << "Date leaving: ";
				cin >> date_out.d >> c >> date_out.m >> c >> date_out.y;
				std::cout << date_out.d << " " << date_out.m << " " << date_out.y << std::endl;


				check_invaild_date = (kiem_tra_ngay_thang_nam(date_in) == false) | (kiem_tra_ngay_thang_nam(date_out) == false) | (date_larger_than(date_out, date_in) < 0);
				if (check_invaild_date)
				{
					std::cout << "Error date! Please try again!" << std::endl;
				}

			} while (check_invaild_date);

			send(connector, (char*)&date_in, sizeof(date), 0);

			send(connector, (char*)&date_out, sizeof(date), 0);

			// Chọn loại phòng dựa vào số thứ tự trong bảng thông tin

			//Nhận thông báo từ server để xem loại phòng này có không?
			recv(connector, (char*)&kind_of_this_room_exist, sizeof(bool), 0);
			if (kind_of_this_room_exist == false)
			{
				std::cout << "Sorry we don't have this kind of room! " << std::endl;
				std::cout << "Please try anothers date!" << std::endl;
			}
		} while (kind_of_this_room_exist == false);

		// Note
		char* note = new char[200];
		int size_note;
		std::cout << "If you have any note please write here: ";
		getchar();
		cin.getline(note, 200);
		size_note = strlen(note);
		std::cout << note << std::endl;
		send(connector, (char*)&size_note, sizeof(int), 0);
		send(connector, (char*)note, strlen(note), 0);
		delete[] note;
	}

	delete[] name_hotel;
	//getchar();
	// Hoa don
	std::cout << "-Invoice of client!" << std::endl;;
	double total_money = 0;
	recv(connector, (char*)&total_money, sizeof(double), 0);
	std::cout << fixed << setprecision(2) << "Total: " << total_money << " USD" << std::endl;
	std::cout << "Have good vacation!" << std::endl;
	return;
}
void cancel_booking(int connector)
{
	char* name_hotel = new char[101];
	bool name_hotel_exist = false;
	std::cout << "Name of hotel:";
	do
	{
		cin.getline(name_hotel, 100);
		int size_of_name_hotel = strlen(name_hotel);

		// Gui ten khach san di
		send(connector, (char*)&size_of_name_hotel, sizeof(int), 0);
		send(connector, (char*)name_hotel, size_of_name_hotel, 0);

		//Nhận thông báo từ server để xem tên khách sạn có hợp lê ko?
		recv(connector, (char*)&name_hotel_exist, sizeof(bool), 0);
		if (name_hotel_exist == false)
		{
			std::cout << "Sorry we don't have this hotel! Please try again:";
		}
	} while (name_hotel_exist == false);
	
	int size_username = strlen(clientA.username);
	// Gui username cho server
	send(connector, (char*)&size_username, sizeof(int), 0);
	send(connector, (char*)clientA.username, size_username, 0);

	int number_booking_of_client = 0;
	// Gui di thong tin cac luot booking cua user do
	recv(connector, (char*)&number_booking_of_client, sizeof(int), 0);
	int order = 0;
	for (int i = 0; i < number_booking_of_client; i++)
	{
		cout << "Booking " << i+1 << ":" << endl;
		customer p;
		recv(connector, (char*)&p.kind_room, sizeof(int), 0);
		recv(connector, (char*)&p.date_in, sizeof(date), 0);
		recv(connector, (char*)&p.date_out, sizeof(date), 0);

		int size_time;
		recv(connector, (char*)&size_time, sizeof(int), 0);
		char* time_dat_phong = new char[size_time + 1];
		recv(connector, (char*)time_dat_phong, size_time, 0);
		time_dat_phong[size_time] = '\0';
		if (p.kind_room == 1)
		{
			std::cout << "Standard Room." << std::endl;
		}
		if (p.kind_room == 2)
		{
			std::cout << "Superior Room." << std::endl;
		}
		if (p.kind_room == 3)
		{
			std::cout << "Deluxe Room." << std::endl;
		}
		if (p.kind_room == 4)
		{
			std::cout << "Suite Room." << std::endl;
		}
		cout << "Date in:" << p.date_in.d << "-" << p.date_in.m << "-" << p.date_in.y << endl;
		cout << "Date out:" << p.date_out.d << "-" << p.date_out.m << "-" << p.date_out.y << endl;
		cout << "Time reservation:" << time_dat_phong << endl;
	}
	cout << "Choose the number of booking to cancel!" << endl;
	cout << "Number of booking want to cancel: ";
	string number_booking_cancel;
	cin >> number_booking_cancel;
	int int_number_booking_cancel;
	string_to_int(number_booking_cancel, int_number_booking_cancel);

	//cout << int_number_booking_cancel << endl;
	send(connector, (char*)&int_number_booking_cancel, sizeof(int), 0);

	bool flag1;

	recv(connector, (char*)&flag1, sizeof(bool), 0);
	cout << flag1 << endl;
	if (flag1 == true)
	{
		cout << "Cancel reservation successfully!" << endl;
	}
	else
	{
		cout << "Can not cancel because time out!" << endl;
	}
	return;
}

void menuClient(int connector) {
	system("cls");
	char c;
	do {
		consoleGraphic Graphic;
		Graphic.gotoxy(43, 9);
		std::cout << "+---------------------+\n";
		Graphic.gotoxy(43, 10);
		std::cout << "|         MENU        |\n";
		Graphic.gotoxy(43, 11);
		std::cout << "+---------------------+\n";
		Graphic.gotoxy(43, 12);
		std::cout << "| 1. Lookup           |";
		Graphic.gotoxy(43, 13);
		std::cout << "| 2. Preservation     |";
		Graphic.gotoxy(43, 14);
		std::cout << "| 3. Cancel Booking   |";
		Graphic.gotoxy(43, 15);
		std::cout << "| 4. Quit	         |";
		Graphic.gotoxy(43, 16);
		std::cout << "+---------------------+";
		c = _getch();
		int flag = 1;
		if (c == '1') {
			send(connector, (char*)&flag, sizeof(int), 0);
			lookup(connector);
		}
		if (c == '2') {
			flag = 2;
			send(connector, (char*)&flag, sizeof(int), 0);
			booking(connector);
		}
		if (c == '3')
		{
			flag = 3;
			send(connector, (char*)&flag, sizeof(int), 0);
			cancel_booking(connector);
		}
	} while (c != '4');
}

void show_image(cv::Mat image, char* name)
{
	cv::imshow(name, image);
	waitKey(0);
}

void recv_image(int socket)
{
	int number_image;
	recv(socket, (char*)&number_image, sizeof(int), 0);
	char* name_room;
	for (int i = 0; i < number_image; i++)
	{
		int size_name_room;
		recv(socket, (char*)&size_name_room, sizeof(int), 0);
		name_room = new char[size_name_room + 1];
		recv(socket, (char*)name_room, size_name_room, 0);
		name_room[size_name_room] = '\0';
		int image_row;
		int image_col;
		int image_size;
		recv(socket, (char*)&image_row, sizeof(int), 0);
		recv(socket, (char*)&image_col, sizeof(int), 0);
		recv(socket, (char*)&image_size, sizeof(int), 0);
		cv::Mat image(image_row, image_col, CV_8UC3);
		int bytes_catched = 0;
		for (int i = 0; i < image_size; i = i + bytes_catched)
		{
			bytes_catched = recv(socket, (char*)image.data + i, image_size - i, 0);
		}
		image.data = (uchar*)image.data;
		threadimage.push_back(thread(show_image, image, name_room));
	}
	return;
}
/*
Pullman Hotel
21/2/2022
23/3/2022
*/
void lookup(int connector) {
	system("cls");
	consoleGraphic gra;
	gra.gotoxy(35, 10);
	std::cout << "Which hotel do you want to choose?";
	char* name_hotel = new char[101];
	
	int tmp = 0;
	do {
		tmp = 0;
		gra.gotoxy(35, 11);
		std::cout << "Hotel: ";
		gra.gotoxy(42, 11);
		cin.getline(name_hotel, 100);
		int size_name_hotel = strlen(name_hotel);
		//cout << name_hotel << endl;
		send(connector, (char*)&size_name_hotel, sizeof(int), 0);
		send(connector, (char*)name_hotel, size_name_hotel, 0);
		recv(connector, (char*)&tmp, sizeof(int), 0);

		if (tmp == 0) {
			gra.gotoxy(42, 11);
			std::cout << "                                               ";
			gra.gotoxy(30, 14);
			std::cout << "Sorry! We can't find this Hotel. Try another one.";
		}
	} while (tmp == 0);

	date in, out;
	bool check_invaild_date;
	do {
		char c;
		gra.gotoxy(35, 12);
		cout << "Date in:";
		gra.gotoxy(44, 12);
		cin >> in.d >> c >> in.m >> c >> in.y;
		gra.gotoxy(35, 13);
		cout << "Date out";
		gra.gotoxy(44, 13);
		cin >> out.d >> c >> out.m >> c >> out.y;
		send(connector, (char*)&in, sizeof(date), 0);
		send(connector, (char*)&out, sizeof(date), 0);
		check_invaild_date = (kiem_tra_ngay_thang_nam(in) == false) | (kiem_tra_ngay_thang_nam(out) == false) | (date_larger_than(out, in) < 0);
		if (check_invaild_date == 1)
		{
			gra.gotoxy(42, 12);
			cout << "                ";
			gra.gotoxy(44, 13);
			cout << "                ";
			gra.gotoxy(44, 14);
			cout << "Something wrong with date. Please check it again.";
		}
	} while (check_invaild_date == 1);
	system("cls");
	char* infoHotel; int len;
	recv(connector, (char*)&len, sizeof(int), 0);
	infoHotel = new char[len + 1];
	recv(connector, (char*)infoHotel, len, 0);
	infoHotel[len] = '\0';
	cout << infoHotel;
	//Nhan hinh anh
	recv_image(connector);
	return;
}

