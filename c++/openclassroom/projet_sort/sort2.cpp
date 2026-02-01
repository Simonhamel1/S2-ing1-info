#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

#include <chrono>

int main() {
    auto start = chrono::high_resolution_clock::now();
    
    vector<int> arr(15000000);
    for (int i = 0; i <  1000 000 000; i++) {
        arr[i] = rand();
    }
    sort(arr.begin(), arr.end());
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Temps: " << duration.count() << " ms" << endl;
    
    return 0;
}