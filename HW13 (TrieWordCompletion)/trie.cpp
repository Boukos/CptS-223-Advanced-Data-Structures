#include "trie.h"

#include <iostream> 
#include <vector>
#include <string>

using namespace std;

trie::trie()
{
	_start.character = '$';
}

trie::charNode::charNode()
{
	end = false;
	character = '\0';
}

void trie::Insert(const char *str, charNode &curr)
{
	if (*str == '\0') {
		curr.end = true;
		return;
	}
	if (curr.branches.size() == 0) {
		curr.branches.resize(26);
	}

	while ((int)*str - 97 < 0 || (int)*str - 97 > 26) {
		str++;
	}

	curr.branches[((int)*str - 97)].character = *str;
	Insert(str + 1, curr.branches[((int)*str - 97)]);
}

void trie::Insert(const char *str)
{
	Insert(str, _start);
}

void trie::Full(charNode& curr, string op, vector<string>& comp)
{
	if (curr.character == '\0') { return; }
	op += curr.character;

	if (curr.end == true)
	{
		comp.push_back(op);
	}
	for (int i = 0; i < curr.branches.size(); i++)
	{
		Full(curr.branches[i], op, comp);
	}
}

void trie::FindWord(charNode& curr, const char *str, string op, vector<string>& comp)
{
	if (curr.character == '$')
	{
		FindWord(curr.branches[(int)*str - 97], str, op, comp);
	}
	else if (str[1] != '\0')
	{
		if (curr.character != *str)
		{
			return;
		}

		str++;
		FindWord(curr.branches[(int)*str - 97], str, op, comp);
	}
	else if (str[1] == '\0')
	{
		if (curr.end == true)
		{
			comp.push_back(op);
		}
		for (int i = 0; i < curr.branches.size(); i++)
		{
			Full(curr.branches[i], op, comp);
		}
	}
}

void trie::FindWord(const char *str, string op, vector<string>& comp)
{
	op = str;
	FindWord(_start, str, op, comp);
}
