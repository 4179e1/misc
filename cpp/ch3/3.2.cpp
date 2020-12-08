#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

class LessThan
{
	public:
		bool operator() (const string &s1, const string &s2)
		{
			return s1.size() < s2.size();
		}
};

int main(void)
{
	vector<string> svec;

	ifstream in_file ("input_file.txt");
	if (!in_file)
	{
		cout << "could not open file\n";
		exit (-1);
	}

//	istream_iterator<string> is(in_file);
//	istream_iterator<string> eof;

	ostream_iterator<string> os(cout, " ");

//	copy(is, eof, back_inserter(svec));
	string word;
	vector<string>::iterator it;
	while (in_file >> word)
	{
		if ((it = find (svec.begin(), svec.end(), word)) == svec.end())
		{
			svec.push_back (word);
		}
	}


	sort(svec.begin(), svec.end(), LessThan());

	copy(svec.begin(), svec.end(), os);

	return 0;
}
