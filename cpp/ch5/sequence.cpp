#include <iostream>
#include <vector>

using namespace std;

class num_sequence
{
	public:
		num_sequence(){}
		virtual ~num_sequence(){}
		virtual int elem (int pos)const = 0;
		virtual const char *what_am_i()const;
		virtual ostream &print(ostream &os = cout) const = 0;
		static int max_elems() {return _max_elems;}
	protected:
		virtual void gen_elems (int pos)const = 0;
		bool check_integrity (int pos, int size) const;
		const static int _max_elems = 1024;
};

bool 
num_sequence::check_integrity (int pos, int size) const
{
	if (pos <= 0 || pos > _max_elems)
	{
		cerr << "!! invalid position: " << pos 
			<< " Cannot honor request\n";
		return false;
	}

	if (pos > size)
	{
		gen_elems (pos);
	}

	return true;
}

ostream& operator<<(ostream &os, const num_sequence &ns)
{
	return ns.print(os);
}

class Fibonacci : public num_sequence
{
	public:
		Fibonacci (int len = 1, int beg_pos = 1)
			: _length(len), _beg_pos (beg_pos) {}
		virtual int elem (int pos) const;
		virtual const char *what_am_i() const {return "Fibonacci";}
		virtual ostream& print (ostream &os = cout) const;
		int length() const {return _length;}
		int beg_pos() const {return _beg_pos;}

	protected:
		virtual void gen_elems (int pos) const;
		int _length;
		int _beg_pos;
		static vector<int> _elems;
};

vector<int> Fibonacci::_elems;

int 
Fibonacci::elem(int pos) const
{
	if (!check_integrity (pos, _elems.size()))
	{
		return 0;
	}

	if (pos > _elems.size())
	{
		Fibonacci::gen_elems (pos);
	}

	return _elems[pos - 1];
};

void 
Fibonacci::gen_elems (int pos) const
{
	if (_elems.empty())
	{
		_elems.push_back(1);
		_elems.push_back(1);
	}

	if (_elems.size() <= pos)
	{
		int ix = _elems.size();
		int n_2 = _elems[ix - 2];
		int n_1 = _elems[ix - 1];

		for (; ix <= pos; ++ix)
		{
			int elem = n_2 + n_1;
			_elems.push_back (elem);
			n_2 = n_1;
			n_1 = elem;
		}
	}
}

ostream& 
Fibonacci::print (ostream &os) const
{
	int elem_pos = _beg_pos - 1;
	int end_pos = elem_pos + _length;

	if (end_pos > _elems.size())
	{
		Fibonacci::gen_elems (end_pos);
	}

	while (elem_pos < end_pos)
	{
		os << _elems[elem_pos++] << ' ';
	}

	return os;
}

int main(void)
{
	Fibonacci fib;

	cout <<"fib: beginning at element 1 for 1 elements: "
		<< fib << endl;

	Fibonacci fib2(16);
	cout << "fib2: beginning at element 1 for 16 elements: "
		<< fib2 << endl;

	Fibonacci fib3 (8, 12);
	cout << "fib3: beginning at element 12 for 8 elements: "
		<< fib3 << endl;

	return 0;
}
