#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;


void map_func (map<string,int>::iterator first, map<string,int>::iterator last) {
	for (; first != last; first++) 
	{
		cout << first->first << '\t' << first->second << endl;
	}
}

int main (void)
{
	map<string,int> words;

	string twords;

	words["linux"] = 1;

	string sa[] = {"microsoft", "windows"};
	set<string> exclusion(sa, sa + 2);

	int i = 1;
	while (cin >> twords)
	{
		if(exclusion.count(twords))
		{
			continue;
		}
		words[twords]++;
	}

	map_func(words.begin(), words.end());

	map<string,int>::iterator it;
	it = words.find("linux");
	if (it != words.end())
	{
		cout << "\"linux\" in map" << endl;
	}

	if (words.count("linux"))
	{
		cout <<"\"linux\" in map" << endl;
	}

	return 0;
}
