#include "Header.h"
#include "trie.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void fileHandle::Process(char *argv[]) {

	trie tree;

	vector<string> FindWord;
	string dictionary, lines, output;
	ifstream infile, wordsEn;
	ofstream outfile;

	infile.open(argv[1]);
	wordsEn.open(argv[2]);
	outfile.open("outfile.txt");

	if (infile.is_open() == false)
	{
		cout << "Failed to open " << argv[1] << endl;
	}
	if (wordsEn.is_open() == false)
	{
		cout << "Failed to open " << argv[2] << endl;
	}

	int v = 0, words = 0;
	while (!wordsEn.eof())
	{
		wordsEn >> dictionary;
		tree.Insert(dictionary.c_str());
		words++;	// count words
	}

	outfile << "Eric Chen 11381898" << endl;
	outfile << "Built trie from " << words << " dictionary words" << endl;

	while (!infile.eof())
	{
		infile >> lines;
		tree.FindWord(lines.c_str(), output, FindWord);

		for (int i = 0; i < FindWord.size(); i++) {
			outfile << FindWord[i];
			outfile << "\n";
		}
		FindWord.clear();
	} // while (!infile.eof())
}

