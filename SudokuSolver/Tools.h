#pragma once
#include <Windows.h>

void Goto(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

HANDLE GetHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}