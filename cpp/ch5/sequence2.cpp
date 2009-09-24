#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

class num_sequence
{
	public:
		virtual ~num_sequence(){}
		int elem (int pos) const;
		const char *what_am_i()const {return typeid(*this).name();}
		static int max_elems() {return _max_elems;}
		int length() const {return _length;}
		int beg_pos() const {return _beg_pos;}
		ostream& print (ostream &os = cout) const;
	protected:
		num_sequence(int len, int bp, vector<int> &re) : _length(len), _beg_pos (bp), _relems(re){}
		virtual void gen_elems (int pos)const = 0;
		bool check_integrity (int pos, int size) const;
		const static int _max_elems = 1024;
		int _length;
		int _beg_pos;
		vector<int> &_relems;
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

int 
num_sequence::elem(int pos) const
{
	if (!check_integrity (pos, _relems.size()))
	{
		return 0;
	}

	if (pos > _relems.size())
	{
		gen_elems (pos);
	}

	return _relems[pos - 1];
};

ostream& operator<<(ostream &os, const num_sequence &ns)
{
	return ns.print(os);
}

ostream& 
num_sequence::print (ostream &os) const
{
	int elem_pos = _beg_pos - 1;
	int end_pos = elem_pos + _length;

	if (end_pos > _relems.size())
	{
		gen_elems (end_pos);
	}

	while (elem_pos < end_pos)
	{
		os << _relems[elem_pos++] << ' ';
	}

	return os;
}

class Fibonacci : public num_sequence
{
	public:
		Fibonacci (int len = 1, int beg_pos = 1)
			: num_sequence(len, beg_pos, _elems) {}

	protected:
		virtual void gen_elems (int pos) const;
		static vector<int> _elems;
};

vector<int> Fibonacci::_elems;


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

void display (ostream &os, const num_sequence &ns, int pos)
{
	os << "The element at position "
		<< pos << " for the "
		<< ns.what_am_i() << " sequence is "
		<< ns.elem(pos) << endl;
}

int main(void)
{
	const int pos = 8;

	Fibonacci fib;
	display (cout, fib, pos);

	return 0;
}
