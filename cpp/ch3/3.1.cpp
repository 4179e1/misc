#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iterator>
#include <stdlib.h>

using namespace std;

void query (map<string, int> &words)
{
	string word;
	cout << "please insert a word to search: q to quit\n";

	cin >> word;
	while (word.size() && word != "q")
	{
		map<string, int>::iterator it;
		if ((it = words.find (word)) != words.end())
		{
			cout << "found! " << it->first << " occur " << it->second << " times\n";
		}
		else
		{
			cout << word << " not found!\n";
		}

		cout << "\nAnother search? (q to quit) ";
		cin >> word;
	}
}

void process (map<string, int> &words, set<string> &exclusion, ifstream &in_file)
{
	string word;
	while (in_file >> word)
	{
		if (exclusion.count(word))
		{
			continue;
		}

		words[word]++;
	}
}

void map_func (map<string,int>::iterator first, map<string,int>::iterator last) {
	for (; first != last; first++) 
	{
		cout << first->first << '\t' << first->second << endl;
	}
}

int main(void)
{
	string sa[] = {"a", "an", "or", "the", "and", "but"};
	set<string> exclusion(sa, sa + 6);

	map<string, int> words;

	ifstream in_file ("input_file.txt");
	if (!in_file)
	{
		cout << "could not open file\n";
		exit (-1);
	}

#if 0
	istream_iterator<string> is(in_file);
	istream_iterator<string> eof;

	ostream_iterator<string> os(cout, " ");
#endif

	process (words, exclusion, in_file);

	map_func (words.begin(), words.end());

	query (words);

	return 0;
}
