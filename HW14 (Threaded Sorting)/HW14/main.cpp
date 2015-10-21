// HW14 Eric Chen 11381898
// Notes:
// Verification not provided.
// NUM_ITEMS in array is 10000, can be set in main.cpp, source.cpp

#include "Source.h"
#include "Sort.h"
#include "string"

#define NUM_ITEMS 10000

using namespace utility;

int main()
{
	cout << "HW 14 Eric Chen 11381898" << endl;
	Sort sort;   // Sorter class

	vector<vector<int>> SortVector; // Vectors of vectors to be sorted

	SortVector.clear();
	SortVector.resize(NUM_ITEMS);   // Vector for sorting
	multArr(SortVector, NUM_ITEMS); // 4 vectors for sorting

	while (true)
	{
		cout << endl << "Menu" << endl;
		cout << "1 = Heapsort" << endl;
		cout << "2 = Insertion sort" << endl;
		cout << "3 = Merge sort" << endl;
		cout << "4 = Quick sort" << endl;
		cout << "5 = All sorting algorithms using threads" << endl;
		cout << "0 = Exit" << endl;

		// Get an option from the user
		string option;
		getline(cin, option);

		if ("1" == option)			// Heap sort
		{
			sort.heapsort(SortVector[0]);		// sorts vector 0
		}
		else if ("2" == option)		// Insertion sort
		{
			sort.insertionsort(SortVector[1]);	// sorts vector 1
		}
		else if ("3" == option)		// Merge sort
		{
			sort.mergesort(SortVector[2]);		// sorts vector 2
		}
		else if ("4" == option)		// Quick sort (vector: toSort[3])
		{
			sort.quicksort(SortVector[3]);		// sorts vector 3
		}
		else if ("5" == option)		// 4 sorting algorithms each on their own thread
		{
			void (Sort::*heapf)(vector<int>&) = &Sort::heapsort;
			void (Sort::*insertf)(vector<int>&) = &Sort::insertionsort;
			void (Sort::*mergef)(vector<int>&) = &Sort::mergesort;
			void (Sort::*quickf)(vector<int>&) = &Sort::quicksort;

			// Thread
			thread heap(heapf, &sort, ref(SortVector[0])), insert(insertf, &sort, ref(SortVector[1])), 
			merge(mergef, &sort, ref(SortVector[2])), quick(quickf, &sort, ref(SortVector[3]));

			// Join
			heap.join();
			insert.join();
			merge.join();
			quick.join();
		}
		else if ("0" == option)		// Exit
		{
			break;
		}
		else
		{
			cout << "Unknown menu option" << endl;
		}
	}

	return 0;
}
