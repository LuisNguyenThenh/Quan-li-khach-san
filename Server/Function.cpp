#include "pch.h"
#include "framework.h"
#include <conio.h>
//
//
void lookup(int connector) {
	int size_name_hotel;
	char* name_hotel;
	Hotel* hotel_ofClient;
	int tmp = 0;
	std::cout << 1234 << std::endl;
	do {
		tmp = 0;
		recv(connector, (char*)&size_name_hotel, sizeof(int), 0);
		name_hotel = new char[size_name_hotel + 1];
		recv(connector, (char*)name_hotel, size_name_hotel, 0);
		name_hotel[size_name_hotel] = '\0';
		hotel_ofClient = get_hotel_from_list(name_hotel);
		if (hotel_ofClient == nullptr) {
			std::cout << 12345 << std::endl;
			send(connector, (char*)&tmp, sizeof(int), 0);
		}
		else {
			tmp = 1;
			std::cout << 1123;
			send(connector, (char*)&tmp, sizeof(int), 0);
		}
	} while (tmp == 0);
	std::cout << name_hotel << std::endl;

	date in, out;

	recv(connector, (char*)&in, sizeof(date), 0);
	recv(connector, (char*)&out, sizeof(date), 0);

	char* infoHotel = hotel_ofClient->Get_info_hotel(in, out);
	int len = strlen(infoHotel);
	send(connector, (char*)&len, sizeof(int), 0);
	send(connector, (char*)infoHotel, len, 0);
	sovle_image(connector, name_hotel, in, out);
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
		const char* tmp = username;
		std::string str(tmp);
		new_booking->user_name = str;
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
		char* buff = new char[DTTMSZ];
		new_booking->ThoigianDatPhong.assign(getDtTm(buff), DTTMSZ);
		delete[] buff;
		hotel->list_booking->add(new_booking);
	}
	//getchar();
	// Hoa don
	send(connector, (char*)&total_money, sizeof(double), 0);

	delete[] name_hotel;
	delete[] username;
	return;
}

void cancel_booking(int connector)
{
	Hotel* hotel;
	bool name_hotel_exist;
	char* name_hotel = new char[100];
	int size_of_name_hotel;
	bool is_hotel_available;
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

	char* user_name;
	int size_user_name;
	recv(connector, (char*)&size_user_name, sizeof(int), 0);
	user_name = new char[size_user_name + 1];
	recv(connector, (char*)user_name, size_user_name, 0);
	user_name[size_user_name] = '\0';

	std::cout << user_name << std::endl;
	
	// Tinh so luong booking cua username
	int number_booking_of_client = 0;
	for (customer* p = hotel->list_booking->head; p; p = p->next)
	{
		if (strcmp(p->user_name.c_str(), user_name) == 0)
		{
			number_booking_of_client++;
		}
	}

	// Gui di thong tin cac luot booking cua user do
	send(connector, (char*)&number_booking_of_client, sizeof(int), 0);
	for (customer* p = hotel->list_booking->head; p; p = p->next)
	{
		if (strcmp(p->user_name.c_str(), user_name) == 0)
		{
			send(connector, (char*)&p->kind_room, sizeof(int), 0);
			send(connector, (char*)&p->date_in, sizeof(date), 0);
			send(connector, (char*)&p->date_out, sizeof(date), 0);
			

			char* c_time_dat_phong;
			string_to_char(p->ThoigianDatPhong, c_time_dat_phong);
			std::cout << c_time_dat_phong << std::endl;
			int size_time =strlen(c_time_dat_phong);
			send(connector, (char*)&size_time, sizeof(int), 0);
			send(connector, (char*)c_time_dat_phong, size_time, 0);
		}
	}
	int number_booking_want_to_cancel;
	recv(connector, (char*)&number_booking_want_to_cancel, sizeof(int), 0);
	bool check = false;
	for (customer* p = hotel->list_booking->head; p; p = p->next)
	{
		if (strcmp(p->user_name.c_str(), user_name) == 0)
		{
			number_booking_want_to_cancel--;
			if (number_booking_want_to_cancel == 0)
			{
				check = true;
				bool flag1;
				if (Valid(p->ThoigianDatPhong.c_str()) == 1)
				{
					flag1 = true;
					hotel->list_booking->remove(p);
				}
				else
				{
					flag1 = false;
				}
				send(connector, (char*)&flag1, sizeof(bool), 0);
				break;
			}
		}
	}
	if (check == false)
	{
		send(connector, (char*)&check, sizeof(bool), 0);
	}
	return;
}

void sovle_image(int sockClient,char* name_hotel,date date_in,date date_out)
{
	Hotel* hotel = get_hotel_from_list(name_hotel);

	std::cout << hotel->name << std::endl;

	int number_image = hotel->Number_kind_of_room_available(date_in, date_out);
	std::cout << number_image << std::endl;
	send(sockClient, (char*)&number_image, sizeof(int), 0);

	for (int i = 1; i <= 4; i++)
	{
		if (hotel->Is_kind_of_room_available_on_date(date_in, date_out, i))
		{
			hotel->Send_image_of_room(sockClient, i);
		}
	}

}
