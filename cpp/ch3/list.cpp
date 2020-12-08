#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

template <typename iteratortype>
void map (iteratortype first, iteratortype last) {
	for (; first != last; first++) 
	{
		cout << *first << '\t';
	}
	cout << endl;
}

int main (void) {
	list<string> slist;

	slist.push_back("konqueror");
	slist.push_back("nautilus");
	slist.push_back("pacman");
	slist.push_back("kwin");

	map (slist.begin(), slist.end());

	list<string>::iterator s;
	s = find (slist.begin(), slist.end(), "konqueror");
	if (s == slist.end()) {
		cout << "string not found" << endl;
	}
	cout << *slist.begin() << *slist.end() << *s <<endl;

	slist.erase(slist.begin(), slist.end());

	map (slist.begin(), slist.end());

	return 0;
}
