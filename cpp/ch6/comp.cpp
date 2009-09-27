#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename elemtype, typename Comp>
class Compare
{
	public:
		Compare (const elemtype &val) : _val (val){};
		bool operator()(const elemtype &val) const
		{return Comp(val, _val);}

		void val(const elemtype &newval) {_val = newval;}
		elemtype val() const {return _val;}
	private:
		elemtype _val;
};

class Iless {
	public:
		bool operator()(const int &i1, const int &i2)
		{return (i1 < i2);}
};

int main(void)
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> va (a, a + 8);

	Compare<int, Iless> cmp(4);
	Compare<int, less<int> > cmp2(4);

	find_if (va.begin(), va.end(), cmp);

	return 0;
}
