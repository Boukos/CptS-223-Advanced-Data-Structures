#include "trie.h"
#include "Header.h"

#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main (int argc, char *argv[])
{
    cout << "Building Trie... Allow up to half a minute." << endl;

    if (argc < 3) 
    {
        cout << "Missing required input file names" << endl;
        return -1;
    }

	fileHandle::Process(argv);

	cout << "Done." << endl;

	system("PAUSE");
    return 0;
}
