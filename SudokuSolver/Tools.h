#pragma once
#include <Windows.h>

const int SC_WIDTH = 120, SC_HEIGHT = 30;

void Goto(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

HANDLE GetHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}