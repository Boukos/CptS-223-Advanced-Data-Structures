#pragma once

#include "PQBase.h"
#include <queue>
#include <vector>

using namespace std;

template <typename T>
class PQ_Heap : public PQBase<T> {
public:
    
    PQ_Heap(int k) {
        _branchNum = k;
	}
    
    bool IsEmpty() const {
        if (_data.empty() == true) {
            return true;
        }
        return false;
    }
    
    void Add(const T& toCopyAndAdd) {
        _data.push_back(toCopyAndAdd);
        int index = ((int)_data.size() - 1);
        int parent = ((index - 1) / _branchNum);
        while ((0 < index) && (_data[parent] < _data[index])) {
            T tmp = _data[parent];
            _data[parent] = _data[index];
            _data[index] = tmp;
            index = parent;
            parent = ((index - 1)/_branchNum);
        }
    }
    
    bool RemoveMax(T& outputItem) {
        if (IsEmpty() == true) {
            return false;
        }
        outputItem = _data[0];
        _data[0] = _data[((int)_data.size() - 1)];
        _data.pop_back();
        sift(0);
        return true;
    }
private:
	void sift(int parent) {
		vector<int> BranchIdx;
		for (int i = 1; i <= _branchNum; i++) {
			if (((parent*_branchNum) + i) < (int)_data.size()) {
				BranchIdx.push_back((parent*_branchNum) + i);
			}
		}
		if (BranchIdx.empty() == true) {
			return;
		}
		T max = _data[BranchIdx[0]];
		int maxIdx = BranchIdx[0];
		for (int i = 0; i < (int)BranchIdx.size(); i++) {
			if (max < _data[BranchIdx[i]]) {
				max = _data[BranchIdx[i]];
				maxIdx = BranchIdx[i];
			}
		}
		if (_data[parent] < _data[maxIdx]) {
			T tmp = _data[parent];
			_data[parent] = _data[maxIdx];
			_data[maxIdx] = tmp;
			sift(maxIdx);
		}
	}
    vector<T> _data;
    int _branchNum;
};
