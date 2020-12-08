#include <iostream>
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <vector>

using namespace std;

#if 1
void oe_sort (vector<int> &ivec, ostream_iterator<int> &odd, ostream_iterator<int> &even)
{
	vector<int> vodd;
	vector<int> veven;

	vector<int>::iterator it;
	for (it = ivec.begin(); it != ivec.end(); it++)
	{
		if ((*it%2) != 0)
		{
			vodd.push_back (*it);
		}
		else
		{
			veven.push_back (*it);
		}
	}

	copy (vodd.begin(), vodd.end(), odd);
	copy (veven.begin(), veven.end(), even);
}
#endif

int main(void) {

	vector<int> ivec;

	istream_iterator<int> is(cin);
	istream_iterator<int> eof;

	ofstream sodd("odd");
	ofstream seven("even");
	if (!sodd || !seven)
	{
		cerr << "could not open file\n";
		exit (-1);
	}

	ostream_iterator<int> odd(sodd, " ");
	ostream_iterator<int> even(seven, " ");

	copy (is, eof, back_inserter(ivec));

	oe_sort (ivec, odd, even);

	return 0;
}
