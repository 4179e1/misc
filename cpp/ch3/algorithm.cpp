#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename iteratortype>
void map (iteratortype first, iteratortype last) {
	for (; first != last; first++) 
	{
		cout << *first << '\t';
	}
	cout << endl;
}

template <typename input_iterator, typename output_iterator, typename elemtype, typename comp>
output_iterator filter (input_iterator first, input_iterator last, output_iterator at, const elemtype &val, comp pred)
{
	while ((first = find_if (first, last, bind2nd (pred, val))) != last)
	{
		cout << "found value: " << *first << endl;
		*at++ = *first++;
	}

	return at;
}

int main (void)
{
	const int elem_size = 8;
	int ia[elem_size] = {12, 8, 43, 0, 6, 21, 3, 7};
	vector<int> ivec(ia, ia + elem_size);

	int ia2[elem_size];
	vector<int> ivec2;

	cout << "filtering integer array for values less than 8\n";
	filter (ia, ia + elem_size, ia2, elem_size, less<int>());

	cout << "filtering integer array for values greater than 8\n";
	filter (ivec.begin(), ivec.end(), back_inserter(ivec2), elem_size, greater<int>());

	map (ivec2.begin(), ivec2.end());

	return 0;
}
