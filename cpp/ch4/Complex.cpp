#include <iostream>

using namespace std;

class Complex
{
	public:
		Complex ();
		Complex (int i);
		Complex (int i, int j);
		Complex& copy(const Complex &rhs);
		void show (void) const;
	private:
		int _i;
		int _j;
};

Complex::Complex()
{
	_i = 1;
	_j = 1;
}

Complex::Complex (int i)
{
	_i = i;
	_j = 1;
}

Complex::Complex (int i, int j)
{
	_i = i;
	_j = j;
}

void
Complex::show () const
{
	cout << _i << '\t' << _j << endl;
}

Complex&
Complex::copy (const Complex &rhs)
{
	if (this != &rhs)
	{
		_i = rhs._i;
		_j = rhs._j;
	}

	return *this;
}


int main (void) 
{
	Complex comp1;
	Complex comp2(10);
	Complex comp3(20, 30);
	Complex comp4 = 40;
	Complex comp5 = (50, 60); /* the same as 'comp5 = 60;' */
	Complex comp6 = comp3;
	Complex comp7;

	comp1.show();
	comp2.show();
	comp3.show();
	comp4.show();
	comp5.show();
	comp6.show();
	comp7.copy(comp6).show();;

	return 0;
}
