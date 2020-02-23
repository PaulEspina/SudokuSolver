#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

#include "Tools.h"

using namespace std;

bool Menu(char digits[9][9]);
bool Enter(char digits[9][9]);
bool Load(char digits[9][9], string arg_path = " ");
bool Save(char digits[9][9], string arg_path = " ");
void Solve(char digits[9][9]);

int main(int argc, char *argv[])
{
	SetConsoleTitleA("Sudoku Solver");
	SetConsoleScreenBufferSize(GetHandle(), {SC_WIDTH, SC_HEIGHT});
	char digits[9][9];
	switch(argc)
	{
	case 1:
		if(!Menu(digits))
		{
			"Program execution failed.\n";
			return -1;
		}
		break;
	case 2:
		if(string(argv[1]) == "-path")
		{
			cout << "USAGE: -path [file path]\n";
		}
		else
		{
			cout << "Argument \"" << argv[1] << "\" is invalid.\n";
		}
		break;
	case 3:
		if(string(argv[1]) == "-path")
		{
			if(!Load(digits, string(argv[2])))
			{
				cout << "Failed loading data.\n";
				return 0;
			}
		}
	default:
		cout << "Invalid arguments.\n";
		break;
	}
	system("cls");
	cout << "SUDOKU SOLVER\n";
	cout << "-------------------------------\n"
	     << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|-----------------------------|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|-----------------------------|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "-------------------------------\n";
	SetConsoleTextAttribute(GetHandle(), 12);
	char temp[9][9];
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			temp[i][j] = digits[i][j];
			Goto(i * 3 + 2 + (i / 3), j + 2 + (j / 3));
			{
				if(temp[i][j] != '0')
					cout << digits[i][j];
			}
		}
	}
	SetConsoleTextAttribute(GetHandle(), 7);
	Goto(0, 14);
	char ans;
	cout << "Solve? y/n\n";
	cout << "\n>> ";
	cin >> ans;
	switch(tolower(ans))
	{
	case 'y':
		Solve(digits);
		break;
	case 'n':
		return -1;
		break;
	default:
		cout << "Invalid input: " << ans << endl;
		return -1;
		break;
	}
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			Goto(i * 3 + 2 + (i / 3), j + 2 + (j / 3));
			{
				if(temp[i][j] == '0')
				{
					cout << digits[i][j];
				}
			}
		}
	}
	Goto(0, 14);
	cout << "Save to file? y/n\n";
	cout << "\n>> " << string(SC_WIDTH - 3, ' ');
	Goto(3, 16);
	cin >> ans;
	system("cls");
	switch(tolower(ans))
	{
	case 'y':
		Save(digits);
		break;
	case 'n':
		return -1;
		break;
	default:
		cout << "Invalid input: " << ans << endl;
		return -1;
		break;
	}
	cout << "\nExiting Program...\n";
	Sleep(1000);
	return 0;
}

bool Menu(char digits[9][9])
{
	cout << "SUDOKU SOLVER\n"
		<< "[1] - Enter Sudoku puzzle.\n"
		<< "[2] - Load Sudoku from a file.\n";
	cout << "\n>> ";
	char opt;
	cin >> opt;
	system("cls");
	switch(opt)
	{
	case '1':
		if(!Enter(digits))
			return 0;
		break;
	case '2':
		if(!Load(digits))
		{
			cout << "Failed loading data.\n";
			return 0;
		}
		break;
	default:
		cout << "[ " << opt << " ] is not accepted.\n";
		system("pause");
		system("cls");
		Menu(digits);
		break;
	}
}

bool Enter(char digits[9][9])
{
	system("cls");
	cout << "SUDOKU SOLVER\n";
	cout << "-------------------------------\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|-----------------------------|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|-----------------------------|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 << "-------------------------------\n";
	SetConsoleTextAttribute(GetHandle(), 12);
	cin.ignore();
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			Goto(j * 3 + 2 + (j / 3), i + 2 + (i / 3));
			char c = _getch();
			digits[j][i] = c;
			_putch(c);
		}
	}
	SetConsoleTextAttribute(GetHandle(), 7);
	return 1;
}

bool Load(char digits[9][9], string arg_path)
{
	string path;
	cout << "SUDOKU SOLVER\n";
	if(arg_path == " ")
	{
		cout << "Enter file path: ";
		cin >> path;
	}	
	else
	{
		path = arg_path;
	}
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

bool Save(char digits[9][9], string arg_path)
{
	string path;
	cout << "SUDOKU SOLVER\n";
	if(arg_path == " ")
	{
		cout << "Enter save path: ";
		cin >> path;
	}
	else
	{
		path = arg_path;
	}
	ofstream save(path);
	if(save.is_open())
	{
		string text[] =
		{
			"-------------------------------\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|-----------------------------|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|-----------------------------|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n",
			"-------------------------------\n"
		};
		cout << "Saving...\n";
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				text[i + 1 + (i / 3)][j * 3 + 2 + (j / 3)] = digits[j][i];
			}
		}
		for(int i = 0; i < 13; i++)
		{
			save << text[i];
		}
	}
	else
	{
		cout << "File not found.\n";
		return 0;
	}
	Goto(0, 2);
	cout << "Saved!" << string(SC_WIDTH - 6, ' ') << endl;
	system("pause");
	system("cls");
	save.close();
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
