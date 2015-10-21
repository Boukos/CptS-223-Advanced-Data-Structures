// Eric Chen 11381898

#ifndef GRADEBOOK223_H
#define GRADEBOOK223_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// As usual, add private helper functions in this class if you need to
class Gradebook
{
private:
	struct Student
	{
		string Name;
		double Grade;

		Student(string& studentName, double studentGrade);
	};

	unsigned int TableSize;
	vector<vector<Student>> HashTable;	// Declare vector<vector<>>: array of arrays
	
	unsigned int hash(const string& key);
	
public:
	Gradebook(void);

	void AddEntry(std::string& studentName, double grade);
	bool GetGrade(std::string& studentName, double& out_gradeIfFound);
};

#endif