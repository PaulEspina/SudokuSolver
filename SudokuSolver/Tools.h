#pragma once
#include <Windows.h>

void Goto(short x, short y)
{
	COORD pos;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}