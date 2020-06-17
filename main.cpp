#include "heap.hpp"
#include <iostream>
using namespace std;

int main() {
    
    

    cout << endl << "Test 1: Create Heap from Array. Insert new Element and remove smallest. Print new smallest." << endl;
    int array[] = {17, 32, 42, 256};
    Heap<int> h(array);

    Counter<int> counter(&h);

    h.insert(20);
    h.extractMin();
    cout << "Test 01  Result: " << h.minimum() << endl;
    h.~Heap();
    cout << "Expected Result: 20" << endl;


    cout << endl << "Counter: " << counter._amountChanges << endl;
    return 0;
}
