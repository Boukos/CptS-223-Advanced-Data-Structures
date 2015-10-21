#include "ArraySorter.h"


ArraySorter::ArraySorter(void)
{
}

void ArraySorter::InsertionSort(int* arr, int n)
{
	InsertionSort(arr, n, 0, 1);
}

void ArraySorter::InsertionSort(int* arr, int n, int startIndex, int gap)
{
	int i, j, tmp;

	for (i = startIndex; i < n; i++) {
		tmp = arr[i];									// tmp stores current value 
		j = i;

		while ((tmp < arr[j - gap]) && (j >= gap)) {	// Loops until we find the sorted position for the current value
			arr[j] = arr[j - gap];						// Shift values that are larger
			j = j - gap;								// Search index decrement
		}
		arr[j] = tmp;									// Set index to current value
	}
	return;
}

// Checks to see if the array is in sorted order
bool ArraySorter::IsSorted(int* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		// If an item is less than the one before it, then we're not sorted
		if (arr[i] < arr[i - 1])
		{
			return false;
		}
	}

	return true;
}

void ArraySorter::ShellSort(int* arr, int n, int* gapVals, int gapValsCount)
{
	// Do an insertion sort pass for each of the gap values
	int i;

	for (i = 0; i < gapValsCount; i++) 
	{
		for (int j = 0; j < gapVals[i]; j++) {
			InsertionSort(arr, n, j, gapVals[i]);	// Insertion sort pass
		}
	}

	if (1 != gapVals[i - 1]) {						// Final case is gap = 1
		InsertionSort(arr, n);
	}
}