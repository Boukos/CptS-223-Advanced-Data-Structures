#pragma once
#include <vector>

using namespace std;

class trie {
public:

	trie();
	void Insert(const char *str);
	void FindWord(const char *str, string op, vector<string>& comp);

private:

	typedef struct charNode {
		charNode();
		bool end;
		char character;
		vector<struct charNode> branches;
	} charNode;

	void Full(charNode& curr, string op, vector<string>& comp);
	void Insert(const char *str, charNode& curr);
	void FindWord(charNode& curr, const char *str, string op, vector<string>& comp);

	charNode _start;
};
