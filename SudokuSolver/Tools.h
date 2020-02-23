#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

const int SC_WIDTH = 120, SC_HEIGHT = 30;

void Goto(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Goto(COORD pos)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

HANDLE GetHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

bool Prompt(string question, bool clear = false, COORD pos = {0,0})
{
	char ans;
	Goto(pos);
	cout << question << endl;
	cout << "\n>> " << string(120 - 3, ' ');
	Goto(pos.X + 3, pos.Y + 2);
	cin >> ans;
	if(clear)
		system("cls");
	switch(tolower(ans))
	{
	case 'y':
		return true;
	case 'n':
		return false;
	default:
		cout << "\'" << ans << "\' is not accepted.\n";
		system("pause");
		system("cls");
		if(Prompt(question))
			return true;
		return false;
	}
}