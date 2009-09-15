#ifndef _STACK_H
#define _STACK_H

#include <string>
#include <vector>

using namespace std;

class Stack {
	public:
		bool push (const string &str);
		bool pop (string &elem);
		bool peek (string &elem);

		bool find(const string &elem) const;
		int count(const string &elem) const;

		bool empty() {return _stack.empty();};
		bool full() {return _stack.size() == _stack.max_size();};

		int size() {return _stack.size();};

	private:
		vector<string> _stack;
};

#endif /* STACK_H */
