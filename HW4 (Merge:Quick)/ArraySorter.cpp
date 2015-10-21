// Eric Chen 11381898

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

// Merges 2 sorted arrays into one sorted array. Returns the sorted array.
int* ArraySorter::Merge(int* arrLeft, int sizeLeft, int* arrRight, int sizeRight)
{
	int *B = new int[sizeof(int) * (sizeLeft + sizeRight)];	// create aux array B
	int i = 0, j = 0, k = 0;

	while ((i < sizeLeft) || (j < sizeRight))		// While array is not empty
	{
		if ((i < sizeLeft) && (j < sizeRight)) {	// If BOTH sides aren't empty
			if (arrLeft[i] < arrRight[j]) {
				B[k++] = arrLeft[i++];
			}
			else
			{
				B[k++] = arrRight[j++];
			}
		}
		else if (i == sizeLeft)					// If arrLeft is empty add the rest of the elements from arrRight
		{
			while (j < sizeRight)
			{
				B[k++] = arrRight[j++];
			}
		}
		else									// If arrRight is empty add rest of the elements from arrLeft
		{
			while (i < sizeLeft)
			{
				B[k++] = arrLeft[i++];
			}
		}
	}
	return B;									// A = B done in MergeSort()
}

// Merge sort structure from tutorial video: https://www.youtube.com/watch?v=TzeBrDU-JaY&spfreload=10
int* ArraySorter::MergeSort2(int* const arr, const int n)
{
	if (n <= 1)									// Base case
	{
		return arr;
	}
	else
	{
		int sizeLeft = n / 2;					// Space for left, size/2
		int sizeRight = n - sizeLeft;			// Space for right, n-left

		int* arrLeft = new int[sizeof(int) * sizeLeft];
		int* arrRight = new int[sizeof(int) * sizeRight];

		for (int i = 0; i < sizeLeft; i++)		// Fill left array
		{
			arrLeft[i] = arr[i];
		}
		for (int i = sizeLeft; i < n; i++)		// Fill right array
		{
			arrRight[i - sizeLeft] = arr[i];
		}

		int* sortedLeft = MergeSort2(arrLeft, sizeLeft);			// Recursive call to sort left
		int* sortedRight = MergeSort2(arrRight, sizeRight);			// Sort right

		return Merge(sortedLeft, sizeLeft, sortedRight, sizeRight);
	}
}

void ArraySorter::MergeSort(int* arr, int n)
{
	int* sorted = MergeSort2(arr, n);

	// Sets arr to sorted array
	for (int i = 0; i < n; i++) {
		arr[i] = sorted[i];
	}
	return;
}

// Structure from QuickSort Implemention slides/class notes
void ArraySorter::QuickSort(int* & a, int left, int right)
{
	if (left + 10 <= right)	{					// Use of recursion in small sub-arrays extends run time
				// Finds median: "Has been shown to reduce running time by 14%
				int center = (left + right) / 2;

				if (a[center] < a[left]) {
					Swap(a[left], a[center]);
				}
				if (a[right] < a[left]) {
					Swap(a[left], a[right]);
				}
				if (a[right] < a[center]) {
					Swap(a[center], a[right]);
				}

				// Pivot position is at right - 1
				Swap(a[center], a[right - 1]);
				int pivot = a[right - 1];

				int i = left, j = right - 1;

				while (true)
				{
					while (a[++i] < pivot) {}			// a[i] >= pivot
					while (pivot < a[--j]) {}			// a[j] <= pivot
					if (i < j) {
						Swap(a[i], a[j]);				// Swap compiled inline; swaps to correct side of pivot
					}
					else
						break;							// Crossed
				}

				Swap(a[i], a[right-1]);					// Restore pivot

				QuickSort(a, left, i-1);				// Sort small elements
				QuickSort(a, i+1, right);				// Sort large elements
			}
	else 	
		// Insertion sort on smaller arrays
		InsertionSort(a, right+1, left+1, 1);

	return;
	}

	// Explicit left and right parameters allow us to in/decrement accordingly
void ArraySorter::QuickSort(int* arr, int n)
{
	QuickSort(arr, 0, n-1);
	return;
}

void ArraySorter::ShellSort(int* arr, int n, int* gapVals, int gapValsCount)
{
	// You implemented this function in the last homework assignment.
	// If you want to paste it here you can, but it will not be graded for 
	// this homework assignment.
}
