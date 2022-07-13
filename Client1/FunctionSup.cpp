#include "pch.h"
#include "framework.h"


bool kiem_tra_nam_nhuan(int y)
{
	if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
	{
		return true;
	}
	return false;

}

bool kiem_tra_ngay_thang_nam(date date)
{
	if (date.d > 31 || date.d <= 0 || date.m > 12 || date.m <= 0 || date.y <= 0) return false;
	int thang[13] = { 0 };

	thang[1] = thang[3] = thang[5] = thang[7] = thang[8] = thang[10] = thang[12] = 31;
	for (int i = 1; i <= 12; i++)
	{
		if (thang[i] == 0) thang[i] = 30;
	}
	bool ok = kiem_tra_nam_nhuan(date.y);
	if (ok == true) thang[2] = 29;
	else thang[2] = 28;
	if (date.d <= thang[date.m]) return true;
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
void string_to_char(string t, char*& s)
{
	s = new char[t.length() + 1];
	for (int i = 0; i < t.length(); i++)
	{
		s[i] = t[i];
	}
	s[t.length()] = '\0';
	return;
}