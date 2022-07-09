#include "pch.h"
#include "framework.h"


void booking(CSocket& connector, Hotel*& list_hotel)
{
	int total_money = 0;
	// Choose hotel
	bool name_hotel_exist;
	char* name_hotel = new char[100];
	int size_of_name_hotel;
	bool is_hotel_available;
	Hotel* hotel;
	do
	{
		// Gui ten khach san di
		connector.Receive((char*)&size_of_name_hotel, sizeof(int), 0);
		connector.Receive(name_hotel, size_of_name_hotel, 0);

		name_hotel[size_of_name_hotel + 1] = '\0';

		//Nhận thông báo từ server để xem tên khách sạn có hợp lên ko?
		hotel = get_hotel_from_list(name_hotel, list_hotel);
		if (hotel == NULL)
		{
			name_hotel_exist = false;
		}
		else
		{
			name_hotel_exist = true;
		}

		connector.Send((char*)&name_hotel_exist, sizeof(bool), 0);
		if (name_hotel_exist == true)
		{
			is_hotel_available = (hotel->Number_room_available() > 0);
			connector.Send((char*)&is_hotel_available, sizeof(bool), 0);
		}

	} while (name_hotel_exist == false || is_hotel_available == false);

	// Số lượng phòng muốn đặt 
	int number_of_room_remaining = hotel->Number_room_available();
	// Nhận từ server số phòng còn trống.

	connector.Send((char*)&number_of_room_remaining, sizeof(int), 0);

	int number_of_room_booking;

	// Choose kind of room		
// Gửi đi số phòng cần đặt
	connector.Receive((char*)&number_of_room_booking, sizeof(int), 0);

	// Xử lý các phòng.
	for (int i = 0; i < number_of_room_booking; i++)
	{

		char* content_kinds_of_room;
		int sz_content_kinds_of_room;

		content_kinds_of_room = hotel->Get_info_hotel();
		sz_content_kinds_of_room = strlen(content_kinds_of_room);


		// Nhận bảng thông tin từ server với các chi tiết cụ thể về từng loại phòng.
		connector.Send((char*)&sz_content_kinds_of_room, sizeof(int), 0);
		connector.Send(content_kinds_of_room, sz_content_kinds_of_room, 0);

		int number_kind_of_room_available = hotel->Number_kind_of_room_available();

		int option_of_client;
		bool kind_of_this_room_exist;

		do
		{

			// Gửi loại phòng cần chọn cho server.
			connector.Receive((char*)&option_of_client, sizeof(int), 0);

			if (option_of_client >= number_kind_of_room_available)
			{
				kind_of_this_room_exist = true;
			}
			else
			{
				kind_of_this_room_exist = false;
			}
			//Nhận thông báo từ server để xem loại phòng này có không?
			connector.Send((char*)&kind_of_this_room_exist, sizeof(bool), 0);
		} while (kind_of_this_room_exist == false);

		//  Ngày vào ở 
		int day_in, month_in, year_in;
		char c;

		connector.Receive((char*)&day_in, sizeof(int), 0);
		connector.Receive((char*)&month_in, sizeof(int), 0);
		connector.Receive((char*)&year_in, sizeof(int), 0);

		// Ngày đi 
		int day_out, month_out, year_out;

		connector.Receive((char*)&day_out, sizeof(int), 0);
		connector.Receive((char*)&month_out, sizeof(int), 0);
		connector.Receive((char*)&year_out, sizeof(int), 0);
	}
	// Note

	int size_note;

	connector.Receive((char*)&size_note, sizeof(int), 0);
	char* note = new char[size_note + 1];
	connector.Receive(note, size_note, 0);
	note[size_note] = '\0';
	//getchar();
	// Hoa don

	connector.Send((char*)&total_money, sizeof(int), 0);
	return;
}