#include <iostream>
#include <fstream>

#include "Tools.h"

using namespace std;

bool Enter(char digits[9][9]);
bool Load(char digits[9][9]);
void Solve(const char digits[9][9]);

int main()
{
	SetConsoleTitleA("Sudoku Solver");
	cout << "SUDOKU SOLVER\n" 
		 << "[1] - Enter Sudoku puzzle.\n"
		 << "[2] - Load Sudoku from a file.\n";
	cout << "\n>> ";
	char opt;
	char digits[9][9];
	cin >> opt;
	system("cls");
	switch(opt)
	{
	case '1':
		if(!Enter(digits))
			return -1;
		break;
	case '2':
		if(!Load(digits))
			return -1;
		break;
	}
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			cout << digits[i][j];
		}
		cout << endl;
	}
	system("pause > 0");
}

bool Enter(char digits[9][9])
{
	return 1;
}

bool Load(char digits[9][9])
{
	cout << "SUDOKU SOLVER\n";
	cout << "Enter file path: ";
	string path;
	cin >> path;
	ifstream load(path);
	if(load.is_open())
	{
		/*for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				digits[i][j] = load.get();
			}
		}*/
		int counter = 0;
		for(char c = load.get(); load.good(); c = load.get())
		{
			if(c == '\n')
				continue;
			digits[(int) counter / 9][counter % 9] = c;
			counter++;
		}
		bool bad = false;
		char valid_data[] = "123456789x";
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				bool found_valid = false;
				for(int k = 0; k < sizeof(valid_data) / sizeof(char); k++)
				{
					if(digits[i][j] == valid_data[k])
					{
						found_valid = true;
					}
				}
				if(!found_valid)
					bad = true;
			}
		}
		if(bad || load.bad())
		{
			cout << "Invalid file data.\n";
			return 0;
		}
	}
	else
	{
		cout << "File not found.\n";
		return 0;
	}
	load.close();
	return 1;
}

void Solve(const char digits[9][9])
{

}
