#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename elemtype>
class LessThan
{
	public:
		LessThan (elemtype val) : _val (val) {}
		elemtype val() const {return _val;}
		void val (elemtype val) {_val = val;}

		bool operator() (elemtype _value) const;

	private:
		elemtype _val;
};

template <typename elemtype>
inline bool LessThan<elemtype>::operator()(elemtype value) const
{
	return value < _val;
}

int main (void)
{
	int ia[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> vec(ia, ia + 8);

	LessThan<int> lt(5);

	vector<int>::const_iterator it = vec.begin();
	vector<int>::const_iterator end = vec.end();

	while((it = find_if (it, end, lt)) != end)
	{
		cout << *it++ << ' ';
	}

	return 0;
}
