#include <conio.h>
#include "framework.h"
#include "pch.h"

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