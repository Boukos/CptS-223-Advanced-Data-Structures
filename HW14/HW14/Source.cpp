#include "Source.h"

using namespace utility;

void utility::randArr(vector<int>& arr, int size) {
    for (int i = 0; i < size; i++) {
        arr.push_back(rand()%1000);
    }
}

void utility::copyArr(vector<int>& toCopy, vector<int>& arr) {
    for (int i = 0; i < toCopy.size(); i++) {
        arr.push_back(toCopy[i]);
    }
}

void utility::multArr(vector<vector<int>>& arr, int size) {
    vector<int> toCopy, r;
    randArr(toCopy, size);

	// Thread
    thread one(copyArr, ref(toCopy), ref(arr[0])), two(copyArr, ref(toCopy), ref(arr[1])),
    three(copyArr, ref(toCopy), ref(arr[2])), four(copyArr, ref(toCopy), ref(arr[3]));

	// Join
    one.join();
    two.join();
    three.join();
    four.join();
}

void utility::display(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
