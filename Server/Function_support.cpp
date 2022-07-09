#include "pch.h"
#include "framework.h"


string int_to_string(int a)
{
	string s;
	stringstream ss;
	ss << a;
	ss >> s;
	return s;
}
string double_to_string(double a)
{
	string s = to_string(a);
	return s;
}
void string_to_char(string t,char*& s)
{
	s = new char[t.length() + 1];
	for (int i = 0; i < t.length(); i++)
	{
		s[i] = t[i];
	}
	s[t.length()] = '\0';
	return;
}
void Load_data_hotel(Hotel* &list_hotel)
{
	ifstream fin;
	fin.open("hotel.txt", ios::in|ios::beg);
	if (fin.is_open() == false) cout << "false open!" << endl;

	int number_hotel;
	fin >> number_hotel;
	
	cout << number_hotel << endl;
	list_hotel = new Hotel[number_hotel];

	//Gán số lương khách sạn ở phần tử đầu tiên của danh sách.
	list_hotel[0].num_hotel = number_hotel;
	for (int i = 0; i < number_hotel; i++)
	{
		
		list_hotel[i].Load_info_hotel(fin);

	}
	//for (int i = 0; i < number_hotel; i++)
	//{
	//	cout << i + 1 << endl;
	//	cout<<list_hotel[i].Get_info_hotel();
	//	cout << list_hotel[i].Number_room_available() << endl;
	//	cout << list_hotel[i].Number_kind_of_room_available() << endl;
	//}

	fin.close();
	return;
}
Hotel* get_hotel_from_list(char* name_hotel, Hotel*& list_hotel)
{
	int number_hotel = list_hotel[0].num_hotel;
	for (int i = 0; i < number_hotel; i++)
	{
		if (strcmp(name_hotel, list_hotel[i].name) == 0)
		{
			return (list_hotel + i);
		}
	}
	return NULL;
}
