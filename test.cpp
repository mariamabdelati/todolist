#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	ofstream f;
	string filename;

	cout << "Please enter a file name to write: ";
	getline(cin, filename);

	f.open(filename.c_str());
	f << "Hello world!";
	f.close();

	cout << "Good job! 'type' or 'cat' your new file to see what it says.\n";
	return 0;
}