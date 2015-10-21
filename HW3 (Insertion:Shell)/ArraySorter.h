#ifndef ARRAYSORTERH
#define ARRAYSORTERH

// As usual you can add additional functions to this class but leave the ones 
// that are already declared the way they are.

class ArraySorter
{
private:
	// Add private helper functions here (if you need them)

public:
	ArraySorter(void);

	void InsertionSort(int* arr, int n, int startIndex, int gap);
	void InsertionSort(int* arr, int n);
	void ShellSort(int* arr, int n, int* gapVals, int gapValsCount);

	// Utility function that's implemented for you to verify that an 
	// array is in correct sorted order.
	static bool IsSorted(int* arr, int n);

	void Swap(int& a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
	};
};

#endif
