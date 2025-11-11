// child.cpp
#include <bits/stdc++.h> 
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "CHILD: No array received from parent." << endl;
        exit(1);
    }

    int n = argc - 1;
    vector<int> arr;
    arr.reserve(n);

    cout << "\n--- Child Process Started ---" << endl;
    cout << "CHILD: Received sorted array: ";
    
    // 1. Convert C-style string arguments back to integers
    for (int i = 0; i < n; i++) {
            arr.push_back(stoi(argv[i + 1]));
            cout << arr[i] << " ";
    }
    cout << endl;


    int key;
    cout << "CHILD: Enter element to search for: ";
    cin >> key;

    auto it = lower_bound(arr.begin(), arr.end(), key);

    if (it != arr.end() && *it == key) {
        int index = distance(arr.begin(), it);
        cout << "CHILD: Element " << key << " FOUND at index " << index << "." << endl;
    } else {
        cout << "CHILD: Element " << key << " NOT found in the array." << endl;
    }
    
    cout << "--- Child Process Finished ---" << endl;
    return 0;
}