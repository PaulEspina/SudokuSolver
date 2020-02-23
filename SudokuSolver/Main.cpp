#include "Tools.h"

bool Menu(char digits[9][9], bool &run);
bool Enter(char digits[9][9]);
bool Load(char digits[9][9], string arg_path = " ");
bool Save(char digits[9][9], string arg_path = " ");
void Solve(char digits[9][9]);

int main(int argc, char *argv[])
{
	SetConsoleTitleA("Sudoku Solver");
	SetConsoleScreenBufferSize(GetHandle(), {SC_WIDTH, SC_HEIGHT});
	bool run = true;
	bool first = true;
	do
	{
		system("cls");
		char digits[9][9];
		bool save = false;
		string save_name;
		if(argc > 1)
		{
			if(!first)
				run = false;
			for(int i = 1; i < argc; i += 2)
			{
				if(string(argv[i]) == "-l")
				{
					if(!Load(digits, string(argv[i + 1])))
					{
						cout << "Failed loading data.\n";
						return 0;
					}
				}
				else if(string(argv[i]) == "-s")
				{
					save_name = argv[i + 1];
					save = true;
				}
				else
				{
					cout << "Invalid arguments.\n";
					return -1;
				}
			}
		}
		else
		{
			if(!Menu(digits, run))
			{
				cout << "Program execution failed.\n";
				system("pause");
				continue;
			}
		}
		if(run)
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
			char temp[9][9];
			for(int i = 0; i < 9; i++)
			{
				for(int j = 0; j < 9; j++)
				{
					temp[i][j] = digits[i][j];
					Goto(i * 3 + 2 + (i / 3), j + 2 + (j / 3));
					if(temp[i][j] != '0')
						cout << digits[i][j];
				}
			}
			SetConsoleTextAttribute(GetHandle(), 7);
			if(Prompt("Solve? y/n", false, {0, 14}))
				Solve(digits);
			else
				continue;
			for(int i = 0; i < 9; i++)
			{
				for(int j = 0; j < 9; j++)
				{
					Goto(i * 3 + 2 + (i / 3), j + 2 + (j / 3));
					if(temp[i][j] == '0')
					{
						cout << digits[i][j];
					}
				}
			}
			if(!save)
			{
				if(Prompt("Save to file? y/n", true, {0, 14}))
					Save(digits);
				else
					continue;
			}
			else
			{
				system("cls");
				Save(digits, save_name);
			}
		}
		first = false;
	} while(run);
	system("cls");
	cout << "Sudoku Solver\n";
	cout << "\nExiting Program...\n";
	Sleep(1000);
	return 0;
}

bool Menu(char digits[9][9], bool &run)
{
	cout << "SUDOKU SOLVER\n"
		 << "[1] - Enter Sudoku puzzle.\n"
		 << "[2] - Load Sudoku from a file.\n"
		 << "[3] - Exit.\n";
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
	case '3':
		run = false;
		break;
	default:
		cout << "\'" << opt << "\' is not accepted.\n";
		system("pause");
		system("cls");
		Menu(digits, run);
		break;
	}
	return 1;
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
	string valid_input = "1234567890";
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			char c;
			bool good;
			do
			{
				Goto(j * 3 + 2 + (j / 3), i + 2 + (i / 3));
				_putch(' ');
				Goto(j * 3 + 2 + (j / 3), i + 2 + (i / 3));
				good = false;
				c = _getch();
				for(unsigned int i = 0; i < valid_input.length(); i++)
				{
					if(valid_input[i] == c || c == '\b')
						good = true;
				}
			}
			while(!good);
			if(c == '\b')
			{
				if(j > 0)
					j -= 2;
				else if(i > 0 && j == 0)
				{
					i--;
					j = 7;
				}
			}
			else
			{
				digits[j][i] = c;
				_putch(c);
			}
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
		string valid_data = "1234567890";
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				bool found_valid = false;
				for(unsigned int k = 0; k < valid_data.length(); k++)
				{
					if(digits[i][j] == valid_data[k])
						found_valid = true;
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
		cout << "Enter file name: ";
		cin >> path;
	}
	else
		path = arg_path;
	ofstream save(path + ".txt");
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
				h_bounds[i].push_back(digits[i][j]); // adds to horizontal bounds
			if(digits[j][i] != '0')
				v_bounds[i].push_back(digits[j][i]); // adds to vertival bounds
			if(digits[j + i / 3][i / 3 + (j % 3) * 3] != '0') // adds to box bounds
				box_bounds[i].push_back(digits[j + i / 3][i / 3 + (j % 3) * 3]);
		}
	}
	char temp[9][9];
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(digits[i][j] != '0')
				temp[i][j] = digits[i][j];
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
						good = false;
					else
						guess++;
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
								j--;
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
