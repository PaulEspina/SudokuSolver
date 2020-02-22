#include <iostream>
#include <fstream>
#include <vector>

#include "Tools.h"

using namespace std;

bool Enter(char digits[9][9]);
bool Load(char digits[9][9]);
void Solve(char digits[9][9]);

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
	cout << endl;
	Solve(digits);
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
		int counter = 0;
		for(char c = load.get(); load.good(); c = load.get())
		{
			if(c == '\n')
				continue;
			digits[(int) counter / 9][counter % 9] = c;
			counter++;
		}
		bool bad = false;
		char valid_data[] = "1234567890";
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
			load.close();
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

void Solve(char digits[9][9])
{
	// Put hints to their respective bounds
	vector<char> h_bounds[9], v_bounds[9], box_bounds[9];
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{

			if(digits[i][j] != '0')
			{
				h_bounds[i].push_back(digits[i][j]); // adds to horizontal bounds
			}
			if(digits[j][i] != '0')
			{
				v_bounds[i].push_back(digits[j][i]); // adds to vertival bounds
			}
			if(digits[j + i / 3][i / 3 + (j % 3) * 3] != '0') // adds to box bounds
			{
				box_bounds[i].push_back(digits[j + i / 3][i / 3 + (j % 3) * 3]);
			}
		}
	}
	char temp[9][9];
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(digits[i][j] != '0')
			{
				temp[i][j] = digits[i][j];
			}
		}
	}
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(digits[i][j] == '0')
			{
				bool good;
				int guess = 48;
				do
				{
					good = true;
					if(guess >= 57)
					{
						good = false;
					}
					else
					{
						guess++;
					}
					for(int k = 0; k < 9; k++ && good)
					{
						if(temp[i][k] == guess || temp[k][j] == guess || temp[i - i % 3 + k / 3][j - j % 3 + k % 3] == guess)
						{
							good = false;
							break;
						}
					}
					if(!good && guess >= 57)
					{
						temp[i][j] = '0';
						do
						{
							if(j > 0)
							{
								j--;
							}
							else if(i > 0 && j == 0)
							{
								i--;
								j = 8;
							}
							guess = temp[i][j];
						}
						while(digits[i][j] != '0');
					}
				}
				while(!good);
				temp[i][j] = guess;
			}
		}
	}
	
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			digits[i][j] = temp[i][j];
		}
	}
}
