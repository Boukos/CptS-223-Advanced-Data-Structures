// Eric Chen 11381898

#include "Gradebook.h"

using namespace std;

Gradebook::Gradebook(void)
{
	// initialize hash table
	TableSize = 1019;	// prime to avoid (index % TableSize) from clustering inputs
	HashTable.resize(TableSize);
}

// New student
Gradebook::Student::Student(string& studentName, double studentGrade)
{
	Name = studentName;
	Grade = studentGrade;
}

// Given a student name as the key, return index
unsigned int Gradebook::hash(const string& key)
{
	unsigned int index = 0;

	for (char c : key)			// For every character c in string key
	{
		index = 37 * index + c;	// Horner's rule
	}

	return index % TableSize;	// To keep large index values within table
}

void Gradebook::AddEntry(string& studentName, double grade)
{
	// Implement this function
	// You must add the student and grade to the hash table UNLESS 
	// a student with the specified name already exists in the table

	int index = hash(studentName);	// Get table index from the key

	for (unsigned int i = 0; i < HashTable[index].size(); i++)	// Traverse array for index
	{
	
		if (HashTable[index][i].Name == studentName)			// Case 1: already exists -> do nothing
		{
			// No duplicates, do nothing
			return;
		}
	}

	// Case 2: does not exist
	Student newStudent = Student(studentName, grade);
	HashTable[index].push_back(newStudent);		// Add student at the end of the array, at index

	return;
}

bool Gradebook::GetGrade(std::string& studentName, double& out_gradeIfFound)
{
	// Implement

	int index = hash(studentName);	// Get table index from the key

	for (unsigned int i = 0; i < HashTable[index].size(); i++)	// Traverse array for index
	{
		if (HashTable[index][i].Name == studentName)			// Case 1: found
		{
			out_gradeIfFound = HashTable[index][i].Grade;
			return true;
		}
	}
	
	return false;	// Case 2: does not exist
}