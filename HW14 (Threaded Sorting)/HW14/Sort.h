#pragma once

#include "Source.h"
#include "PQ_Heap.h"

class Sort {
public:
    void quicksort(vector<int>& toSort);
    void mergesort(vector<int>& toSort);
    void insertionsort(vector<int>& toSort);
    void heapsort(vector<int>& toSort);
private:
    void insertionsort(vector<int>& toSort, int startIndex, int gap);
    void Quicksort(vector<int>& toSort, int i, int j);
    void mergesort2(vector<int>& toSort, int i, int j);
    void merge(vector<int>& toSort, int i, int k, int j);
};
