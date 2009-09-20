#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Triangular_iterator
{
	public:
		Triangular_iterator (int index) : _index (index - 1){}
		bool operator==(const Triangular_iterator&) const;
		bool operator!=(const Triangular_iterator&) const;
		int operator*() const;
		Triangular_iterator& operator++();
		Triangular_iterator operator++(int);
	private:
		void check_integrity() const;
		int _index;
};

class Triangular
{
	friend class Triangular_iterator;
	public:
		typedef Triangular_iterator iterator;
		Triangular();
		Triangular(int len);
		Triangular(int len, int beg_pos);
		int length() const {return _length;}
		int beg_pos() const {return _beg_pos;}
		int length(int val) {_length = val;}
		int beg_pos(int val) {_beg_pos = val;}
		int elem(int pos) const;
		Triangular& copy (const Triangular &rhs);

		void display (int length, int beg_pos, ostream &os) const;

		bool next(int &val) const;
		void next_reset() {_next = _beg_pos -1;}

		static bool is_elem (int);
		static void gen_elements (int length);
		static void gen_elems_to_value (int value);


		Triangular_iterator begin() const
		{
			return Triangular_iterator (_beg_pos);
		}
		Triangular_iterator end() const
		{
			return Triangular_iterator (_beg_pos + _length);
		}
//		static void display (int length, int beg_pos, ostream &os = cout);
	private:
		int _length;
		int _beg_pos;
		mutable int _next;

		static const int _max_elems = 1024;
		static vector<int> _elems;
};


vector<int> Triangular::_elems;

ostream& operator<<(ostream &os, const Triangular &rhs)
{
	os << "( " << rhs.beg_pos() << ", "
		<< rhs.length() << " )";

	rhs.display(rhs.length(), rhs.beg_pos(), os);
	return os;
}

istream& operator>>(istream &is, Triangular &rhs)
{
	char ch1, ch2;
	int bp, len;

	is >> ch1 >> bp >> ch2 >> len;

	rhs.beg_pos (bp);
	rhs.length (len);
	rhs.next_reset();

	return is;
}

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

	int elem_cnt = _beg_pos + _length;
    if ( _elems.size() < elem_cnt )
         gen_elements( elem_cnt );
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

bool
Triangular::is_elem (int value)
{
	if ( !_elems.size() || _elems[ _elems.size() - 1] < value)
		gen_elems_to_value (value);

	vector<int>::iterator found_it;
	vector<int>::iterator end_it = _elems.end();

	found_it = find (_elems.begin(), end_it, value);

	return found_it != end_it;
}

void
Triangular::gen_elems_to_value (int value)
{
	int ix = _elems.size();
	if (!ix)
	{
		_elems.push_back (1);
		ix = 1;
	}

	while (_elems[ix - 1] < value && ix < _max_elems )
	{
		++ix;
		_elems.push_back (ix * (ix + 1) / 2);
	}

	if (ix == _max_elems)
	{
		cerr << "Triangular Sequence: oops: value too large " << value << " -- exceeds max sizeof " << _max_elems << endl;
	}
}

void
Triangular::gen_elements (int length)
{
	if (length < 0 || length > _max_elems)
	{
		cerr << "error\n";
		return;
	}

	if (_elems.size() < length)
	{
		int ix = _elems.size() ? _elems.size() + 1 : 1;

		for (; ix <= length; ++ix)
		{
			_elems.push_back (ix * (ix + 1) / 2);
		}
	}
}


inline bool
Triangular_iterator::operator==(const Triangular_iterator &rhs) const
{
	return _index == rhs._index;
}

void
Triangular::display (int length, int beg_pos, ostream &os) const
{
	if (length <= 0 || beg_pos <= 0)
	{
		cerr << "invalid parameters -- unable to fulfill request: "
			<< length << ", " << beg_pos << endl;
		return;
	}

	int elems = beg_pos + length - 1;

	if (_elems.size() < elems)
	{
		gen_elements (elems);
	}

	for (int ix = beg_pos - 1; ix < elems; ++ix)
	{
		os << _elems[ix] << ' ';
	}
}

inline bool
Triangular_iterator::operator!=(const Triangular_iterator &rhs) const
{
	return !(*this == rhs);
}

inline int
Triangular_iterator::operator*() const
{
	check_integrity();
	return Triangular::_elems[_index];
}

class iterator_overflow
{
};

inline void
Triangular_iterator::check_integrity() const
{
	if (_index >= Triangular::_max_elems)
	{
		throw iterator_overflow();

		if (_index >= Triangular::_elems.size())
		{
			Triangular::gen_elements (_index + 1);
		}
	}
}

inline 
Triangular_iterator& Triangular_iterator::operator++()
{
	++_index;
	check_integrity();
	return *this;
}

inline
Triangular_iterator Triangular_iterator::operator++(int)
{
	Triangular_iterator tmp = *this;
	++_index;
	check_integrity();
	return tmp;
}

void prog1(void)
{
	char ch;
	bool more = true;

	while (more)
	{
		cout << "Enter value: ";
		int ival;
		cin >> ival;

		bool is_elem = Triangular::is_elem (ival);
		cout << ival << (is_elem ? " is " : " is not ")
			<< "an element in the Triangular series.\n"
			<< "Another value?(y/n)";

		cin >> ch;
		if (ch == 'n' || ch == 'N')
		{
			more = false;
		}
	}
}

void prog2(void)
{
	Triangular tri (20, 12);
	Triangular::iterator it = tri.begin();
	Triangular::iterator end_it = tri.end();
	cout << "Triangular Series of " << tri.length() << " elements\n";
	//cout << tri << endl;
	while (it != end_it)
	{
		cout << *it << ' ';
		++it;
	}

	cout << endl;
}

void prog3(void)
{
	Triangular tri (6, 3);
	cout << tri << '\n';

	Triangular tri2;
	cin >> tri2;
	cout << tri2;
}

int main(void)
{
	//prog1();
	//prog2();
	prog3();
	return 0;
}
