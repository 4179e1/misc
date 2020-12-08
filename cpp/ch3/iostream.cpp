#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "useage: prog <filename>\n";
		exit(-1);
	}

	ifstream in_file(argv[1]);
	if (!in_file)
	{
		cout << "unable to open " << argv[1] << endl;
		exit (-2);
	}

	istream_iterator<string> is (in_file);
	istream_iterator<string> eof;

	vector<string> text;
	copy(is, eof, back_inserter(text));

	sort (text.begin(), text.end());

	ostream_iterator<string> os (cout, "\n");
	copy(text.begin(), text.end(), os);

	return 0;
}

