#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

namespace utility 
{
    void randArr(vector<int>& arr, int size);
    void copyArr(vector<int>& toCopy, vector<int>& arr);
    void multArr(vector<vector<int>>& arr, int size);
    void display(const vector<int>& arr);
}
