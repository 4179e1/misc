#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

template <typename elemtype>
inline elemtype *begin (vector<elemtype> &vec)
{
	return vec.empty() ? NULL : &vec[0];
}

template <typename elemtype>
inline elemtype *end (vector<elemtype> &vec)
{
	return vec.empty() ? NULL : &vec[vec.size()];
}

template <typename iteratortype, typename elemtype>
iteratortype find (const iteratortype first, const iteratortype last, const elemtype &value)
{
	for (;first != last; first++)
	{
		if (*first == value)
		{
			return first;
		}
	}

	return last;
}

int main (void)
{
	int 	ia[] = {1, 1, 2, 3, 5, 8, 13, 21};
	double	da[] = {1.5, 2.0, 2.5, 3.0, 3.5, 4.0};
	string	sa[] = {"pooh", "piglet", "eeyore", "tigger"};

#if 0
	cout << *find (ia, ia + 8, ia[3]) << '\t'
		 << *find (da, da + 6, da[3]) << '\t'
		 << *find (sa, sa + 4, sa[3]) << endl;

	vector<string> svec (sa, sa + 4);
	cout << *find (svec.begin(), svec.end(), svec[3]) << endl;
#endif

	list<int> ilist (ia, ia + 8);
	cout << *find (ilist.begin(), ilist.end(), 13) << endl;

	return 0;
}
