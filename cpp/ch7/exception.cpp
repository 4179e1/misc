#include <iostream>
#include <stdlib.h>

using namespace std;

int ex_div (int a, int b) {
	if (b == 0)
		throw ("error: zero division");

	return (a / b);
}

int main(void) 
{
	int a;
	int b;

	cout << "Input a: ";
	cin >> a;
	cout << "Input b: ";
	cin >> b;

	try {

		cout << a << " divide by " << b << " is " << ex_div(a, b) << endl;
	}
	catch (const char* str)
	{
		cout << str << endl;
		exit (-1);
	}
	return 0;
}
