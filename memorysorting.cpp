#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <memory>

void runTime(std::chrono::time_point<std::chrono::system_clock> start){ // passes the start time.
    auto stop = std::chrono::high_resolution_clock::now(); // gets the time that the runTime function has been called.
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); // calculates the time elapsed.
    std::cout << "\nTime taken by function: " << duration.count() << " microseconds" << std::endl; // prints elapsed time
}

void vecSort(std::vector<int> &sortVec){ // passing by reference.
    std::sort(sortVec.begin(), sortVec.end()); // sorts the vector.
}

std::vector<int> vecSortReturnVal(std::vector<int> sortVec){ // vector stored on heap, data stored on the stack. Different name as vecSort takes has the same variable passed into it.
    std::sort(sortVec.begin(), sortVec.end()); // sorts the vector.

    return sortVec; // returns the new vector.
}

void vecSort(std::vector<std::unique_ptr<int>> &sortVecSmartPtr){ // smart pointer.
    std::sort(sortVecSmartPtr.begin(), sortVecSmartPtr.end(), [](const std::unique_ptr<int>& a, const std::unique_ptr<int>& b){
        return *a < *b; // comparator compares prt values, rather than memory addresses.
    }); // sorts the vector.
}

bool comp(int* a, int* b){
    return *a < *b; // comparator compares prt values, rather than memory addresses.
}

void vecSort(std::vector<int*> &sortVecPtr){ // regular pointer.
    std::sort(sortVecPtr.begin(), sortVecPtr.end(), comp); // sorts the vector.

    for(auto ptr : sortVecPtr){ // deletes ptrs after use.
        delete ptr;
    }
}

int main(){
    int x;
    int vecSize = 10000;

    std::vector<int> sortVec; // initializes a vector with 10,000 elements. Vector object is on the stack, data in on the heap.
    std::vector<std::unique_ptr<int>> sortVecSmartPtr;
    std::vector<int*> sortVecPtr;
    sortVec.reserve(vecSize);
    sortVecSmartPtr.reserve(vecSize);
    sortVecPtr.reserve(vecSize);

    srand(time(nullptr));

    for(int i=0;i<vecSize;i++){ // indexes through the vector, assigning each position a random number.
        sortVec.push_back(rand() %vecSize);
        sortVecSmartPtr.push_back(std::make_unique<int>(rand() %vecSize)); // Allocate and store a random number. The pointer is stored in the stack, the data in the heap.
        sortVecPtr.push_back(new int(rand() % vecSize)); // Allocate and store a random number. The pointer is stored in the stack, the data in the heap.
    }

    std::cout << sortVec.size() << "\n";

    auto start = std::chrono::high_resolution_clock::now(); // start time.
    vecSort(sortVec); // sorts vector by reference.
    runTime(start); // calcultates function run time.

    start = std::chrono::high_resolution_clock::now(); // start 
    vecSort(sortVecSmartPtr); // uses smart pointers.
    runTime(start); // calcultates function run time.

    start = std::chrono::high_resolution_clock::now(); // start 
    vecSort(sortVecPtr); // uses regular pointers.
    runTime(start); // calcultates function run time.
    
    start = std::chrono::high_resolution_clock::now(); // start 
    std::vector<int> returnVec = vecSortReturnVal(sortVec); // sorts vector, then passes the value to new vector 'returnVec.'
    runTime(start); // calcultates function run time.
} // both sortVec, returnVec, and sortVecPtr are automatically destroyed as they have gone out of scope.
