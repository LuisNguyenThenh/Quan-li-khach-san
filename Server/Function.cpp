#include "pch.h"
#include "framework.h"
#include <conio.h>
//
//
void lookup(CSocket& connector) {
	std::cout << "+-------------------------+\n";
	std::cout << "|       INFORMATION       |\n";
	std::cout << "+-------------------------+\n";
	std::cout << "| 1. Hotel                |\n";
	std::cout << "| 2. Booking information  |\n";
	std::cout << "+-------------------------+\n";
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

void booking(int connector)
{
	std::cout << "VO DUOC LAN 2" << std::endl;
	int size_username;
	// Gui username cho server
	recv(connector, (char*)&size_username, sizeof(int), 0);

	char* username = new char[size_username + 1];
	recv(connector, (char*)username, size_username, 0);
	username[size_username] = '\0';
	std::cout << username << std::endl;


	double total_money = 0;
	// Choose hotel
	bool name_hotel_exist;
	char* name_hotel = new char[100];
	int size_of_name_hotel;
	bool is_hotel_available;

	Hotel* hotel;
	do
	{
		// Gui ten khach san di
		recv(connector, (char*)&size_of_name_hotel, sizeof(int), 0);
		recv(connector, (char*)name_hotel, size_of_name_hotel, 0);

		name_hotel[size_of_name_hotel] = '\0';
		std::cout << name_hotel << std::endl;
		//Nhận thông báo từ server để xem tên khách sạn có hợp lên ko?
		hotel = get_hotel_from_list(name_hotel);
		if (hotel == NULL)
		{
			name_hotel_exist = false;
		}
		else
		{
			name_hotel_exist = true;
		}
		send(connector, (char*)&name_hotel_exist, sizeof(bool), 0);

	} while (name_hotel_exist == false);

	//// Số lượng phòng muốn đặt 
	//int number_of_room_remaining = hotel->Number_room_available();
	//// Nhận từ server số phòng còn trống.

	//send(connector,(char*)&number_of_room_remaining, sizeof(int), 0);

	int number_of_room_booking;

	// Choose kind of room		
// Gửi đi số phòng cần đặt
	recv(connector, (char*)&number_of_room_booking, sizeof(int), 0);

	// Xử lý các phòng.
	for (int i = 0; i < number_of_room_booking; i++)
	{
		customer* new_booking = new customer;
		
		copy_string(new_booking->user_name, username);
		//char* content_kinds_of_room;
		//int sz_content_kinds_of_room;

		//content_kinds_of_room = hotel->Get_info_hotel();
		//sz_content_kinds_of_room = strlen(content_kinds_of_room);


		//// Nhận bảng thông tin từ server với các chi tiết cụ thể về từng loại phòng.
		//send(connector,(char*)&sz_content_kinds_of_room, sizeof(int), 0);
		//send(connector,content_kinds_of_room, sz_content_kinds_of_room, 0);

		/*int number_kind_of_room_available = hotel->Number_kind_of_room_available();*/

		int option_of_client;
		date date_in;
		date date_out;
		bool kind_of_this_room_exist;
		recv(connector, (char*)&option_of_client, sizeof(int), 0);
		std::cout << option_of_client << std::endl;
		do
		{

			// Gửi loại phòng cần chọn cho server.
			recv(connector, (char*)&date_in, sizeof(date), 0);
			std::cout << date_in.d << " " << date_in.m << " " << date_in.y << std::endl;
			recv(connector, (char*)&date_out, sizeof(date), 0);

			std::cout << date_out.d << " " << date_out.m << " " << date_out.y << std::endl;


			kind_of_this_room_exist = hotel->Is_kind_of_room_available_on_date(date_in, date_out, option_of_client);
			//Nhận thông báo từ server để xem loại phòng này có không?
			send(connector, (char*)&kind_of_this_room_exist, sizeof(bool), 0);
		} while (kind_of_this_room_exist == false);



		new_booking->date_in = date_in;
		new_booking->date_out = date_out;
		new_booking->kind_room = option_of_client;
		// Note
		total_money += double(hotel->Price_of_kind_room(option_of_client) * double(distance_time(date_in, date_out) + 1));
		std::cout << total_money << std::endl;
		std::cout << " " << hotel->Price_of_kind_room(option_of_client) << std::endl;
		std::cout << " " << distance_time(date_in, date_out) << std::endl;
		int size_note;

		recv(connector, (char*)&size_note, sizeof(int), 0);
		char* note = new char[size_note + 1];
		recv(connector, note, size_note, 0);
		note[size_note] = '\0';
		std::cout << note << std::endl;
		new_booking->note = note;
		hotel->list_booking->add(new_booking);
	}
	//getchar();
	// Hoa don
	send(connector, (char*)&total_money, sizeof(double), 0);

	delete[] name_hotel;
	delete[] username;
	return;
}

// nhan lenh tra cuu hoac dat phong tu client
void getRequirefromMenu(int sockClient)
{
	int flag;
	recv(sockClient, (char*)&flag, sizeof(int), 0);
	if (flag == 1)
	{
		// look up
		getRequirefromLookup(sockClient);
	}
	if (flag == 0) {
		// preservation
		//std::cout << "kjsdf" << std::endl;
		booking(sockClient);
	}
}
// nhan lenh tra cuu ten khach san, ngay vao o va ngay roi di.

void send_image(int socket, const char* name_file)
{
	cv::Mat image;
	image = cv::imread(name_file, 1);
	int image_row = image.rows;
	int image_col = image.cols;
	int image_size = image.total() * image.elemSize();

	send(socket, (char*)&image_row, sizeof(int), 0);
	send(socket, (char*)&image_col, sizeof(int), 0);
	send(socket, (char*)&image_size, sizeof(int), 0);
	send(socket, (char*)image.data, image_size, 0);
	//cv::imshow("Hotel", image);
	return;
}

void getRequirefromLookup(int sockClient) {
	int flag;
	send_image(sockClient, "hotel.jpg");
	recv(sockClient, (char*)&flag, sizeof(int), 0);
	if (flag == 1) {

	}
	if (flag == 0) {

	}
	return;
}