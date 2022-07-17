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

		//Nhận thông báo từ server để xem tên khách sạn có hợp lên ko?
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


		//char* content_kinds_of_room = new char[500];
		//int sz_content_kinds_of_room;

		//// Nhận bảng thông tin từ server với các chi tiết cụ thể về từng loại phòng.
		//recv(connector,(char*)&sz_content_kinds_of_room, sizeof(int), 0);
		//recv(connector,content_kinds_of_room, sz_content_kinds_of_room, 0);
		//content_kinds_of_room[sz_content_kinds_of_room + 1] = '\0';

		//// Xuất bảng thông tin nhận từ server
		//std::cout << content_kinds_of_room << std::endl;

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


void menuClient(int connector) {
	std::cout << "+---------------------+\n";
	std::cout << "|         MENU        |\n";
	std::cout << "+---------------------+\n";
	std::cout << "| 1. Lookup           |\n";
	std::cout << "| 2. Preservation     |\n";
	std::cout << "+---------------------+\n";

	char c = _getch();
	int flag = 1;
	if (c == '1') {
		send(connector, (char*)&flag, sizeof(int), 0);
		lookup(connector);
	}
	if (c == '2') {
		flag = 0;
		send(connector, (char*)&flag, sizeof(int), 0);
		booking(connector);
	}
}

void show_image(cv::Mat image)
{
	cv::imshow("Hotel", image);
	waitKey(0);
}
void recv_image(int socket)
{
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

	threadimage.push_back(thread(show_image, image));
	return;
}
void lookup(int connector) {
	std::cout << "+-------------------------+\n";
	std::cout << "|       INFORMATION       |\n";
	std::cout << "+-------------------------+\n";
	std::cout << "| 1. Hotel                |\n";
	std::cout << "| 2. Booking information  |\n";
	std::cout << "+-------------------------+\n";
	recv_image(connector);

	char c = _getch();
	int flag = 1;
	if (c == '1') {
		send(connector, (char*)&flag, sizeof(int), 0);
	}
	if (c == '2') {
		flag = 0;
		send(connector, (char*)&flag, sizeof(int), 0);

	}
	return;
}

