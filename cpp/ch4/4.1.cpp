#include <iostream>
#include <string>
#include "Stack.h"

int main(void)
{
	Stack st;
	string str;

	while (cin >> str && ! st.full())
	{
		st.push (str);
	}

	if (st.empty())
	{
		cout << '\n' << "oops: no strings were read\n";
		return 0;
	}

	cout << '\n' << "Read in " << st.size() << " strings!\n"
		<< "The strings, in revers order: \n";

	if (st.find("a"))
	{
		cout << "There are " << st.count("a") << " 'a' in stack";
	}


	while (st.size())
	{
		if (st.pop(str))
		{
			cout << str << ' ';
		}
	}

	cout << '\n' << "There are now " << st.size()
		<< " elements in the stack!\n";
}
