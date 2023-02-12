#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>

using namespace std;


int Binary(int n) {
	int b = 0;
	int rem, i = 1;

	while (n != 0 && i < 1000) {
		rem = n % 2;
		n /= 2;
		b += rem * i;
		i *= 10;
	}

	return b;
}

string compare(string s1, string s2,int variables)
{
	int diff = 0;
	string res;
	if (variables == 2)
	{
		res = "__";
		if (s1[0] == s2[0])
			res[0] = s1[0];
		else {
			diff++;
			res[0] = '_';
		}

		if (s1[1] == s2[1])
			res[1] = s1[1];
		else {
			diff++;
			res[1] = '_';
		}
		
		if (diff > 2)
			return "None";

		return res;

	}
	else if (variables == 3)
	{
		res = "___";
		if (s1[0] == s2[0])
			res[0] = s1[0];
		else {
			res[0] = '_';
			diff++;
		}

		if (s1[1] == s2[1])
			res[1] = s1[1];
		else {
			res[1] = '_';
			diff++;

		}

		if (s1[2] == s2[2])
			res[2] = s1[2];
		else {
			res[2] = '_';
			diff++;

		}

		if (diff > 1)
			return "None";
		else if (diff > 2)
			return "Error";
		else
			return res;
	}
	else
		return "Error";


}

int concat(int a, int b)
{
	string s1, s2,s;
	s1 = to_string(a);
	s2 = to_string(b);
	s = s1 + s2;
	int c = stoi(s);
	return c;
}

int main()
{

	ifstream infile;
	string cinf;
	cout << "Please write the name of file to input from : ";
	cin >> cinf;
	cout << endl;
	infile.open(cinf);
	string input;
	string arr[100];
	int i = 0;
	if (infile.fail())
	{
		cout << "Error, file didn't work.";
	}
	else
	{
		
		while (getline(infile, input))
		{
			arr[i] = input;
			i++;
		}
	}


	int TestCase = stoi(arr[0]);
	//cout << "Number of TestCase " << TestCase << endl;
/*
	for (int x = 1; x <= TestCase; x++)
	{
		string tem = arr[x];
		cout << x << "th Test Case's number of variables is " << tem[0] << endl;
		cout << x << "th Test Case's number of minterms is " << tem[2] << endl;

	}
*/
	ofstream myfile;
	myfile.open("output.txt");
	// KMap
	for (int w = 1; w <= TestCase; w++)
	{
		myfile << w << endl;
		myfile << "K-Map for ";
		string temp = arr[w];
		myfile << temp << endl;
		char* s = &temp[2];
		int num = atoi(s);
		int N = num * 2 + 2;

		if ((temp[0]) == '2')
		{
			int kmap[2][2];
			for (int p = 0; p < 2; p++)
			{
				for (int q = 0; q < 2; q++)
				{
					for (int t = 4; t <= N; t = t + 2)
					{
						if (concat(p, q) == Binary(temp[t])) {
							kmap[p][q] = 1;
						}
						else {
							kmap[p][q] = 0;
						}

					}
				}
			}
			for (int p = 0; p < 2; p++)
			{
				for (int q = 0; q < 2; q++)
				{
					myfile << kmap[p][q] << " ";
				}
				myfile << endl;
			}
		}

	
		
		if (temp[0] == '3')
		{
			int kmap[2][4];
			for (int p = 0; p < 2; p++)
			{
				for (int q = 0; q < 4; q++)
				{
					for (int t = 4; t <= N; t = t + 2)
					{
						if (p == (Binary(temp[t]) / 100))
						{
							if (Binary(temp[t]) % 100 == 0)
								kmap[p][0] = 1;
							else if (Binary(temp[t]) % 100 == 1)
								kmap[p][1] = 1;
							else if (Binary(temp[t]) % 100 == 11)
								kmap[p][2] = 1;
							else if (Binary(temp[t]) % 100 == 10)
								kmap[p][3] = 1;
							
						}
						else
							kmap[p][q] = 0;
					}
				}
			}
			for (int p = 0; p < 2; p++)
			{
				for (int q = 0; q < 4; q++)
				{
					myfile << kmap[p][q] << " ";
				}
				myfile << endl;
			}
		}
		
		myfile << endl;
		

	}
	

	myfile << endl << endl;
	// Minimized expression
	for (int w = 1; w <= TestCase; w++)
	{
		myfile << w << endl;
		myfile << endl << "Minimized expression for ";
		string temp = arr[w];
		myfile << temp << endl;
		char* s = &temp[2];
		int num = atoi(s);
		int N = num * 2 + 2;
		// N is last minterm

		// grouping by number of 1s
		if ((temp[0]) == '2')
		{
			int count = 0;
			int c[3] = { 0,0,0 };
			string grp[3][3];

			for (int t = 4; t <= N; t = t + 2)
			{
				int count = 0;
				if (Binary(temp[t]) % 10 == 1)
					count++;
				if (Binary(temp[t]) % 100 >= 10)
					count++;

				string bin = "00";
				if (Binary(temp[t]) < 10)
				{
					bin[0] = '0';
					bin[1] = to_string(Binary(temp[t]))[0];
				}
				else
					bin = to_string(Binary(temp[t]));
				
				if (count == 0) {
					grp[0][c[0]] = bin;
					c[0]++;
				}
				if (count == 1) {
					grp[1][c[1]] = bin;
					c[1]++;
				}
				if (count == 2) {
					grp[2][c[2]] = bin;
					c[2]++;
				}
				/*
				cout << "Column grouping depending on 1s" << endl;
				for (int j = 0; j < c[0]; j++)
					{
						cout << grp0[j] << " ";
					}
				cout << endl;
				for (int j = 0; j < c[1]; j++)
				{
					cout << grp1[j] << " ";
				}
				cout << endl;
				for (int j = 0; j < c[2]; j++)
				{
					cout << grp2[j] << " ";
				}
				cout << endl;
				*/
				for (int u = 0; u < 2; u++)
				{
					for (int b = 0; b < c[u]; b++)
					{
						for (int f = 0; f < c[u+1]; f++)
						{
							if (compare(grp[u][b], grp[u+1][f], 2) == "None")
							{
								if (grp[u][b] == "1")
									myfile << "A";
								else if (grp[u][b] == "0")
									myfile << "A'";

								if (grp[u][b] == "1")
									myfile << "B";
								else if (grp[u][b] == "0")
									myfile << "B'";
								myfile << " + ";
							}
							else
							{
								string tem = compare(grp[u][b], grp[u + 1][f], 2);
								if (tem[0] == '0')
									myfile << "A'";
								if (tem[0] == '1')
									myfile << "A";

								if (tem[1] == '0')
									myfile << "B'";
								if (tem[1] == '1')
									myfile << "B";
								myfile << " + ";

							}

						}
					}
				}
			}
			myfile << endl;

		}

		if ((temp[0]) == '3')
		{
			int count = 0;
			// c[4] is position in array
			int c[4] = { 0,0,0,0};
			string grp[4][4] = { "___", "___","___","___","___","___","___","___","___","___","___","___","___","___","___","___" };

			for (int t = 4; t <= N; t = t + 2)
			{

				int count = 0;

				if (Binary(temp[t]) % 10 == 1)
					count++;
				if (Binary(temp[t]) % 100 >= 10)
					count++;
				if (Binary(temp[t]) % 1000 >= 100)
					count++;

				string bin = "000";
				if (Binary(temp[t]) < 10)
				{		
					bin[0] = '0';
					bin[1] = '0';
					bin[2] = to_string(Binary(temp[t]) % 10)[0];

				}
				else if (Binary(temp[t]) < 100)
				{
					bin[0] = '0';
					bin[1] = '1';
					bin[2] = to_string(Binary(temp[t]) % 10)[0];

				}
				else
					bin = to_string(Binary(temp[t]));
				
				if (count == 0) {
					grp[0][c[0]] = bin;
					c[0]++;
				}
				if (count == 1) {
					grp[1][c[1]] = bin;
					c[1]++;
				}
				if (count == 2) {
					grp[2][c[2]] = bin;
					c[2]++;
				}
				if (count == 3) {
					grp[3][c[3]] = bin;
					c[3]++;
				}
			}
			// cout the grouping by 1s
			/*	cout << "Column grouping depending on 1s" << endl;
				for (int j = 0; j < c[0]; j++)
				{
					cout << grp[0][j] << " ";
				}
				cout << endl;
				for (int j = 0; j < c[1]; j++)
				{
					cout << grp[1][j] << " ";
				}
				cout << endl;
				for (int j = 0; j < c[2]; j++)
				{
					cout << grp[2][j] << " ";
				}
				cout << endl;
				for (int j = 0; j < c[3]; j++)
				{
					cout << grp[3][j] << " ";
				}
				cout << endl;
			*/
				int l = 0;
				string col3[5];
				for (int u = 0; u < 3; u++)
				{
					for (int s = 0; s < c[u]; s++)
					{
						// first column
						for (int v = 0; v < c[s + 1]; v++)
						{
							string srg;
							srg = compare(grp[u][s], grp[u + 1][v], 3);
							if (srg == "None")
							{
								string tp = grp[u][s];
								if (tp[0] == '1')
									myfile << "A";
								else if (tp[0] == '0')
									myfile << "A'";
								if (tp[1] == '1')
									myfile << "B";
								else if (tp[1] == '0')
									myfile << "B'";
								if (tp[2] == '1')
									myfile << "C";
								else if (tp[2] == '0')
									myfile << "C'";
								myfile << " + ";

							}
							else if (srg == "Error")
							{
								break;
							}
							else {
								col3[l] = compare(grp[u][s], grp[u + 1][v], 3);
								l++;

							}

						}

					}
				}

				// second column
				for (int g = 0; g < l-1; g++)
				{
					if (compare(col3[g], col3[g + 1], 3) == "None")
					{
						string str = col3[g];
						if (str[0] == '1')
							myfile << "A";
						else if (str[0] == '0')
							myfile << "A'";

						if (str[1] == '1')
							myfile << "B";
						else if (str[1] == '0')
							myfile << "B'";

						if (str[2] == '1')
							myfile << "C";
						else if (str[2] == '0')
							myfile << "C'";
						
						myfile << " + ";

					}
					else if (compare(col3[g], col3[g + 1], 3) == "Error")
					{
						break;
					}
					else
					{
						string str2 = compare(col3[g], col3[g + 1], 3);
						if (str2[0] == '1')
							myfile << "A";
						else if (str2[0] == '0')
							myfile << "A'";

						if (str2[1] == '1')
							myfile << "B";
						else if (str2[1] == '0')
							myfile << "B'";

						if (str2[2] == '1')
							myfile << "C";
						else if (str2[2] == '0')
							myfile << "C'";
						
						myfile << " + ";

					}

				}

		}
		myfile << endl;

	}
	cout << "Output is saved in output.txt" << endl;

		return 0;
}