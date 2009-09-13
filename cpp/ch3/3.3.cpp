#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "debug_macro.h"

using namespace std;

typedef vector<string> vstring;

void show_map (map<string, vstring> &families, ostream &os)
{
	map<string, vstring>::iterator it = families.begin();

	while (it != families.end())
	{
		os << "The " << it->first << " family ";
		if (it->second.empty())
		{
			os << " have no children\n";
		}
		else
		{
			os << " has " << it->second.size() << " children: ";
			vector<string>::iterator vit = it->second.begin();
			while (vit != it->second.end())
			{
				os << *vit << " ";
				++vit;
			}
			os << endl;
		}
		++it;
	}
}

void populate_map (map<string, vstring> &families, ifstream &file)
{
	string textline;

	while (getline(file, textline))
	{
		string fam_name;
		vector<string> child;
		string::size_type pos = 0, prev_pos = 0, 
						  text_size = textline.size();

		while (( pos = textline.find_first_of (' ', pos)) != string::npos)
		{
			string::size_type end_pos = pos - prev_pos;

			if (!prev_pos)
			{
				DEBUG_PRINT;
				fam_name = textline.substr(prev_pos, end_pos);
			}
			else
			{
				DEBUG_PRINT;
				child.push_back (textline.substr(prev_pos, end_pos));
			}

			prev_pos = ++pos;

		}

		if (!prev_pos)
		{
			DEBUG_PRINT;
			fam_name = textline.substr(prev_pos, pos - prev_pos);
		}
		else if (prev_pos < text_size)
		{
			DEBUG_PRINT;
			child.push_back (textline.substr(prev_pos, pos - prev_pos));
		}

		if (!families.count(fam_name))
		{
			DEBUG_PRINT;
			families[fam_name] = child;
		}
		else
		{
			DEBUG_PRINT;
			cerr << "already have a " << fam_name << " in map\n";
		}
	}
}

int main(void)
{
	map<string, vstring> families;
	ifstream file("families.txt");
	if (!file)
	{
		cerr << "could not open file\n";
		return (-1);
	}
	
	populate_map (families, file);
	show_map (families, cout);

	return 0;
}
