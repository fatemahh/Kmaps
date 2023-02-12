#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

	ifstream infile;
	infile.open("input.txt");

	if (infile.fail())
	{
		cout << "Error, file didn't work.";
	}
	else
	{
		string in;
		while (getline(infile, in))
		{
			cout << in << endl;
		}
	}


	return 0;
}