#include "pch.h"
#include "framework.h"


std::string int_to_string(int a)
{
	std::string s;
	std::stringstream ss;
	ss << a;
	ss >> s;
	return s;
}
std::string double_to_string(double a)
{
	std::string s = std::to_string(a);
	return s;
}
void string_to_char(std::string t, char*& s)
{
	s = new char[t.length() + 1];
	for (int i = 0; i < t.length(); i++)
	{
		s[i] = t[i];
	}
	s[t.length()] = '\0';
	return;
}

void copy_string(char*& s, char*& t)
{
	s = new char[strlen(t) + 1];
	for (int i = 0; i < strlen(t); i++)
	{
		s[i] = t[i];
	}
	s[strlen(t)] = '\0';
	return;
}


void Load_data_hotel()
{
	std::ifstream fin;
	fin.open("hotel.txt", std::ios::in | std::ios::beg);
	if (fin.is_open() == false) std::cout << "false open!" << std::endl;

	int number_hotel;
	fin >> number_hotel;

	char c[2];
	fin.getline(c, 1);
	list_hotel = new Hotel[number_hotel];

	list_hotel[0].num_hotel = number_hotel;
	for (int i = 0; i < number_hotel; i++)
	{
		list_hotel[i].Load_info_hotel(fin);
	}
	//for (int i = 0; i < number_hotel; i++)
	//{
	//	std::cout << i + 1 << std::endl;
	//	std::cout<<list_hotel[i].Get_info_hotel();
	//	std::cout << list_hotel[i].Number_room_available() << std::endl;
	//	std::cout << list_hotel[i].Number_kind_of_room_available() << std::endl;
	//}

	fin.close();
	return;
}
Hotel* get_hotel_from_list(char* name_hotel)
{
	std::cout << "in Here!";
	int number_hotel = list_hotel[0].num_hotel;
	for (int i = 0; i < number_hotel; i++)
	{
		//std::cout << list_hotel[i].name;
		if (strcmp(name_hotel, list_hotel[i].name) == 0)
		{
			//std::cout << "True" << std::endl;
			return (list_hotel + i);
		}
	}
	return NULL;
}

bool kiem_tra_nam_nhuan(int y)
{
	if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
	{
		return true;
	}
	return false;

}

bool kiem_tra_ngay_thang_nam(int day, int m, int y)
{
	if (day > 31 || day <= 0 || m > 12 || m <= 0 || y <= 0) return false;
	int thang[13] = { 0 };

	thang[1] = thang[3] = thang[5] = thang[7] = thang[8] = thang[10] = thang[12] = 31;
	for (int i = 1; i <= 12; i++)
	{
		if (thang[i] == 0) thang[i] = 30;
	}
	bool ok = kiem_tra_nam_nhuan(y);
	if (ok == true) thang[2] = 29;
	else thang[2] = 28;
	if (day <= thang[m]) return true;
	return false;
}

int date_larger_than(date date1, date date2)
{
	if (date1.y > date2.y) return 1;
	if (date1.y < date2.y) return -1;

	if (date1.m > date2.m) return 1;
	if (date1.m < date2.m) return -1;

	if (date1.d > date2.d) return 1;
	if (date1.d < date2.d) return -1;

	return 0;
}

int tim_ngay(date date)
{
	int thang[13] = { 0 };

	thang[1] = thang[3] = thang[5] = thang[7] = thang[8] = thang[10] = thang[12] = 31;
	for (int i = 1; i <= 12; i++)
	{
		if (thang[i] == 0) thang[i] = 30;
	}
	bool ok = kiem_tra_nam_nhuan(date.y);
	if (ok == true) thang[2] = 29;
	else thang[2] = 28;
	int sum = 0;
	for (int i = 1; i < date.m; i++)
	{
		sum += thang[i];
	}
	sum += date.d;
	return sum;
}

int distance_time(date date1, date date2)
{
	if (date1.y > date2.y) return 0;
	int so_ngay_thu_1 = tim_ngay(date1);
	int so_ngay_thu_2 = tim_ngay(date2);
	if (date1.y == date2.y)
	{
		return so_ngay_thu_2 - so_ngay_thu_1;
	}
	if (date2.y == date1.y + 1)
	{
		return (365 - so_ngay_thu_1 + kiem_tra_nam_nhuan(date1.y)) + so_ngay_thu_2;
	}
	if (date2.y >= date1.y + 2)
	{
		int new_y1 = date1.y + 1;
		int new_y2 = date2.y - 1;
		so_ngay_thu_1 = (365 - so_ngay_thu_1 + kiem_tra_nam_nhuan(date1.y));
		int so_boi_cua_4 = int(date2.y / 4) - int((date1.y - 1) / 4);
		int so_boi_cua_100 = int(date2.y / 100) - int((date1.y - 1) / 100);
		int so_boi_cua_400 = int(date2.y / 400) - int((date1.y - 1) / 400);
		int kq = so_ngay_thu_1 + so_ngay_thu_2 + (new_y2 - new_y1 + 1) * 365 + so_boi_cua_4 - so_boi_cua_100 + so_boi_cua_400;
		return abs(kq);
	}
	return 0;
}