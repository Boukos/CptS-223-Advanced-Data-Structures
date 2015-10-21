// Eric Chen
// 11381898
// CptS 223 - Advanced Data Structures
// Homework assignment #1

#include "ReversibleStack.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Display(ReversibleStack& rs) {
	// CHECK Implement this function (use only Push, Pop and IsEmpty member functions of stack)
	// CHECK After the function completes, the stack should be unmodified (see assignment instructions)

	// we make a new stack, the loop through the existing ones, popping off elements and putting them on the new stack
	// then we go through the new stack and pop them all off and put them back on the original one
	ReversibleStack newStack;
	while (!rs.IsEmpty()) {
		int value = rs.Pop();
		cout << value << (rs.IsEmpty() ? "" : " "); 		// OCD-level perfectionism to make sure there isn't a space behind the last number
		newStack.Push(value);			// pushes stack rs onto newStack
	}
	while (!newStack.IsEmpty()) {
		rs.Push(newStack.Pop());		// pushes newStack back onto stack rs
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Missing required argument for input file." << endl;
		return 1;                                     	// return nonzero for failure
	}

	ifstream inFile;
	inFile.open(argv[1], ifstream::in);

	if (!inFile.is_open()) {
		cout << "Could not open: " << argv[1] << endl;
		return 2;
	}

	ReversibleStack rs;
	string line;

	// Process the command on each line
	while (!inFile.eof()) {
		getline(inFile, line);

		if (0 == line.compare(0, 6, "header")) {
			cout << "Eric Chen - 11381898";     // Display the header line here, as the instructions describe
		}
		else if (line.compare(0, 4, "push") == 0) {
			int val = stoi(line.substr(5));				// takes everything after characters 'push'. Substr takes index 5 to the end of the string and stoi turns it into an int
			rs.Push(val);
		}
		else if (line.compare(0, 3, "pop") == 0) {
			rs.Pop();                             		// pop and print the top item
		}
		else if (line.compare(0, 7, "isempty") == 0) {
			cout << endl << (rs.IsEmpty() ? "true" : "false");    // print true if empty, otherwise false
		}
		else if (line.compare(0, 7, "reverse") == 0) {
			rs.Reverse();
		}
		else if (line.compare(0, 7, "display") == 0) {
			cout << endl;
			Display(rs);
		}
		else {
			cout << "Unknown command: " << line;
		}
	}

	// Complete
	inFile.close();
	cout << endl << "Done" << endl;

	system("PAUSE");
	return 0;                                           // return 0 for success

}