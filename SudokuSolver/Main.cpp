#include "Tools.h"

const int N = 9;
const int SUB_N = 3;

bool Menu(char digits[N][N], bool &run);
bool Enter(char digits[N][N]);
bool Load(char digits[N][N], string arg_path = " ");
bool Save(char digits[N][N], string arg_path = " ");
bool Solve(char digits[N][N]);

int main(int argc, char *argv[])
{
	SetConsoleTitleA("Sudoku Solver");
	SetConsoleScreenBufferSize(GetHandle(), {SC_WIDTH, SC_HEIGHT});
	bool run = true;
	bool first = true;
	do
	{
		char digits[N][N];
		bool save = false;
		bool load = false;
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
					system("cls");
					load = true;
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
			if(!load && run)
			{
				if(!Menu(digits, run))
				{
					cout << "Program execution failed.\n";
					system("pause");
					first = false;
					continue;
				}
			}
		}
		else
		{
			if(!Menu(digits, run))
			{
				cout << "Program execution failed.\n";
				system("pause");
				first = false;
				continue;
			}
		}
		if(run)
		{
			if(save && load)
			{
				cout << "Solving...\n";
				if(!Solve(digits))
				{
					cout << "Puzzle is impossible to solve.\n";
				}
				else
				{
					cout << "Solved.\n";
					Save(digits, save_name);
					cout << "File saved as \"" << save_name << ".txt\"\n";
				}
				system("pause");
				system("cls");
				exit(0);
			}
			else
			{
				system("cls");
				cout << "\n-------------------------------\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|-----------------------------|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|-----------------------------|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
					 <<   "-------------------------------\n";
				SetConsoleTextAttribute(GetHandle(), 12);
				char temp[N][N];
				for(int i = 0; i < N; i++)
				{
					for(int j = 0; j < N; j++)
					{
						temp[i][j] = digits[i][j];
						Goto(i * SUB_N + 2 + (i / SUB_N), j + 2 + (j / SUB_N));
						if(temp[i][j] != '0')
							cout << digits[i][j];
					}
				}
				SetConsoleTextAttribute(GetHandle(), 7);
				if(Prompt("Solve? y/n", false, {0, 14}))
				{
					if(!Solve(digits))
					{
						system("cls");
						cout << "Puzzle is impossible to solve.\n";
						first = false;
						system("pause");
						continue;
					}
				}
				else
				{
					first = false;
					continue;
				}
				for(int i = 0; i < N; i++)
				{
					for(int j = 0; j < N; j++)
					{
						Goto(i * SUB_N + 2 + (i / SUB_N), j + 2 + (j / SUB_N));
						if(temp[i][j] == '0')
						{
							cout << digits[i][j];
						}
					}
				}
				if(save)
				{
					system("cls");
					if(Save(digits, save_name))
					{
						Goto(0, 2);
						cout << "Saved!" << string(SC_WIDTH - 6, ' ') << endl;
						system("pause");
						system("cls");
					}
					else
					{
						cout << "Program execution failed.\n";
						system("pause");
						first = false;
						continue;
					}
				}
				else
				{
					if(Prompt("Save to file? y/n", true, {0, 14}))
					{
						if(Save(digits))
						{
							Goto(0, 2);
							cout << "Saved!" << string(SC_WIDTH - 6, ' ') << endl;
							system("pause");
							system("cls");
						}
						else
						{
							cout << "Program execution failed.\n";
							system("pause");
							first = false;
							continue;
						}
					}
					else
					{
						first = false;
						continue;
					}
				}
			}
		}
		first = false;
	} while(run);
	system("cls");
	cout << "\nExiting Program...\n";
	Sleep(1000);
	system("cls");
	return 0;
}

bool Menu(char digits[N][N], bool &run)
{
	system("cls");
	cout << "SUDOKU SOLVER\n"
		 << "[1] - Enter Sudoku puzzle.\n"
		 << "[2] - Load Sudoku from a file.\n"
		 << "[SUB_N] - Exit.\n";
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

bool Enter(char digits[N][N])
{
	system("cls");
	cout << "\n-------------------------------\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|-----------------------------|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|-----------------------------|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "|[ ][ ][ ]|[ ][ ][ ]|[ ][ ][ ]|\n"
		 <<   "-------------------------------\n";
	SetConsoleTextAttribute(GetHandle(), 12);
	cin.ignore();
	string valid_input = "1234567890";
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			char c;
			bool good;
			do
			{
				Goto(j * SUB_N + 2 + (j / SUB_N), i + 2 + (i / SUB_N));
				_putch(' ');
				Goto(j * SUB_N + 2 + (j / SUB_N), i + 2 + (i / SUB_N));
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

bool Load(char digits[N][N], string arg_path)
{
	string path;
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
			digits[(int) counter / N][counter % N] = c;
			counter++;
		}
		bool bad = false;
		string valid_data = "1234567890";
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
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

bool Save(char digits[N][N], string arg_path)
{
	string path;
	if(arg_path == " ")
	{
		cout << "Enter file name: ";
		cin >> path;
		path += ".txt";
	}
	else
		path = arg_path;
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
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				text[i + 1 + (i / SUB_N)][j * SUB_N + 2 + (j / SUB_N)] = digits[j][i];
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
	save.close();
	return 1;
}

bool Solve(char digits[N][N])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(digits[i][j] != '0')
			{
				for(int k = 0; k < N; k++)
				if((digits[i][k] == digits[i][j] && j != k) || 
				   (digits[k][j] == digits[i][j] && i != k) || 
				   digits[i - i % SUB_N + k / SUB_N][j - j % SUB_N + k % SUB_N] == digits[i][j] && !(i == i - i % SUB_N + k / SUB_N && j == j - j % SUB_N + k % SUB_N))
				{
					return 0;
				}
			}
		}
	}
	char temp[N][N];
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(digits[i][j] != '0')
				temp[i][j] = digits[i][j];
		}
	}
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
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
					for(int k = 0; k < N; k++)
					{
						if(temp[i][k] == guess || temp[k][j] == guess || temp[i - i % SUB_N + k / SUB_N][j - j % SUB_N + k % SUB_N] == guess)
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
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			digits[i][j] = temp[i][j];
		}
	}
	return 1;
}
