#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	fstream file(argv[1]);
	if(file.is_open())
	{
		system("cls");
		for(char c = file.get(); file.good(); c = file.get())
		{
			cout << c;
		}
		file.close();
		system("pause > 0");
	}
	else
	{
		cout << "The file could not be modified/created.\n";
	}
}