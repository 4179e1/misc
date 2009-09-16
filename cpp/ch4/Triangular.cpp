#include <iostream>
#include <vector>

using namespace std;

class Triangular
{
	public:
		Triangular();
		Triangular(int len);
		Triangular(int len, int beg_pos);
		int elem(int pos) const;
		Triangular& copy (const Triangular &rhs);

		bool next(int &val) const;
		void next_reset() {_next = _beg_pos -1;}
	private:
		int _length;
		int _beg_pos;
		mutable int _next;
		static vector<int> _elems;
};

vector<int> Triangular::_elems;

Triangular::Triangular()
{
	_length = 1;
	_beg_pos = 1;
	_next = 0;
}

Triangular::Triangular(int len)
{
	_length = len > 0 ? len : 1;
	_beg_pos = 1;
	_next = 0;
}

Triangular::Triangular(int len, int beg_pos)
{
	_length = len > 0 ? len : 1;
	_beg_pos = beg_pos > 0 ? beg_pos : 1;
	_next = beg_pos - 1;
}

int
Triangular::elem (int pos) const
{
	return _elems[pos - 1];
}

bool
Triangular::next (int &value) const
{
	if (_next < _beg_pos + _length - 1)
	{
		value = _elems[_next++];
		return true;
	}
	return false;
}

Triangular&
Triangular::copy (const Triangular &rhs)
{
	if (this != &rhs)
	{
		_length = rhs._length;
		_beg_pos = rhs._beg_pos;
		_next = rhs._beg_pos - 1;
	}

	return *this;
}

int main(void)
{
	return 0;
}
