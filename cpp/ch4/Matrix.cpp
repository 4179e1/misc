#include <iostream>

using namespace std;

class Matrix
{
	public:
		Matrix();
		Matrix(int row, int col);
		Matrix(const Matrix &rhs);
		Matrix& copy(const Matrix &rhs);
		~Matrix();
	private:
		int _row, _col;
		double *_pmat;
};

Matrix::Matrix()
{
	_row = _col = 1;
	_pmat = new double[1];
}

Matrix::Matrix(int row, int col)
{
	_row = row;
	_col = col;
	_pmat = new double[row * col];
}

Matrix::Matrix(const Matrix &rhs)
: _row(rhs._col), _col(rhs._col) 
{
	int cnt = _row * _col;
	_pmat = new double[cnt];

	for (int i = 0; i < cnt; i++)
	{
		_pmat[i] = rhs._pmat[i];
	}
}

Matrix::~Matrix()
{
	delete [] _pmat;
}

Matrix&
Matrix::copy (const Matrix &rhs)
{
	if (this != &rhs)
	{
		_row = rhs._row;
		_col = rhs._col;
	}

	return *this;
}

int main(void) {
	Matrix mat1;
	Matrix mat2(4, 4);

	{
		Matrix mat3 = mat2;
	}

	return 0;
}
