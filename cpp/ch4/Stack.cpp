#include "Stack.h"
#include <algorithm>

bool
Stack::pop (string &elem)
{
	if (empty())
	{
		return false;
	}

	elem = _stack.back();
	_stack.pop_back();
	return true;
}

bool
Stack::peek (string &elem)
{
	if (empty())
	{
		return false;
	}

	elem = _stack.back();

	return true;
}

bool
Stack::push (const string &elem)
{
	if (full())
	{
		return false;
	}

	_stack.push_back (elem);
	return true;
}

bool
Stack::find (const string &elem) const
{
	vector<string>::const_iterator end_it = _stack.end();
	return ::find( _stack.begin(), _stack.end(), elem) != end_it;
}

int
Stack::count (const string &elem) const
{
	return ::count(_stack.begin(), _stack.end(), elem);
}
