#include "Sort.h"

#define NUM_ITEMS 10000

void Sort::Quicksort(vector<int>& toSort, int i, int j) {
	int l = i, r = j;
	int tmp = 0, piv = toSort[(i + j) / 2];
	while (i <= j) {
		while (toSort[i] < piv) {
			i++;
		}
		while (toSort[j] > piv) {
			j--;
		}
		if (i <= j) {
			tmp = toSort[i];
			toSort[i] = toSort[j];
			toSort[j] = tmp;
			i++;
			j--;
		}

	}
	if (l < j) {
		Quicksort(toSort, l, j);
	}
	if (i < r) {
		Quicksort(toSort, i, r);
	}
}

void Sort::quicksort(vector<int>& toSort) {
	Quicksort(toSort, 0, (int)toSort.size() - 1);
	cout << "Quick sort: done." << endl;
}

void Sort::merge(vector<int>& toSort, int i, int k, int j) {
	int i2, j2, k2, b[NUM_ITEMS];		// Aux array b
	i2 = i;
	k2 = i;
	j2 = k + 1;
	while (i2 <= k && j2 <= j){			// If BOTH sides aren't empty
		if (toSort[i2] < toSort[j2])	// If (i<j)
		{
			b[k2] = toSort[i2];
			k2++;
			i2++;
		}
		else 
		{
			b[k2] = toSort[j2];			// If arrLeft is empty add the rest of the elements from arrRight
			k2++;
			j2++;
		}
	}
	while (i2 <= k){
		b[k2] = toSort[i2];
		k2++;
		i2++;
	}
	while (j2 <= j){
		b[k2] = toSort[j2];
		k2++;
		j2++;
	}
	for (i2 = i; i2 < k2; i2++)			// A = B
	{
		toSort[i2] = b[i2];
	}
}

void Sort::mergesort2(vector<int>& toSort, int i, int j) {
	int k = 0;
	if (i < j) {
		k = (i + j) / 2;
		mergesort2(toSort, i, k);
		mergesort2(toSort, k + 1, j);
		merge(toSort, i, k, j);
	}
}

void Sort::mergesort(vector<int>& toSort) {
	mergesort2(toSort, 0, (int)toSort.size() - 1);
	cout << "Merge sort: done." << endl;
}

void Sort::insertionsort(vector<int>& toSort, int startIndex, int gap) {
	int i = startIndex, j = 0, tmp;
	while (i < toSort.size()) {
		tmp = toSort[i];							// tmp stores current value 
		j = i;
		while (gap <= j &&  tmp < toSort[j - gap]) {// Loops until we find the sorted position for the current value
			toSort[j] = toSort[j - gap];			// Shift values that are larger
			j = j - gap;							// Search index decrement
		}
		toSort[j] = tmp;							// Set index to current value
		i++;
	}
}

void Sort::insertionsort(vector<int>& toSort) {
	insertionsort(toSort, 0, 1);
	cout << "Insertion sort: done." << endl;
}

void Sort::heapsort(vector<int>& toSort) {
	PQ_Heap<int> heap(1000);
	int size = (int)toSort.size();
	for (int i = 0; i < size; i++) {
		heap.Add((int)toSort[i]);
	}
	cout << "Heap sort: done." << endl;
}












