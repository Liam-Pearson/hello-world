#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <memory>

int vecSize = 10000;

void runTime(std::chrono::time_point<std::chrono::system_clock> start){ // passes the start time.
    auto stop = std::chrono::high_resolution_clock::now(); // gets the time that the runTime function has been called.
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); // calculates the time elapsed.
    std::cout << "\nTime taken by function: " << duration.count() << " microseconds" << std::endl; // prints elapsed time
}

void vecSort(std::vector<int> &sortVec){ // passing by reference.
    auto start = std::chrono::high_resolution_clock::now(); // start time.
    std::sort(sortVec.begin(), sortVec.end()); // sorts the vector.
    runTime(start); // calcultates function run time.
}

std::vector<int> vecSortReturnVal(std::vector<int> sortVec){ // vector stored on heap, data stored on the stack. Different name as vecSort takes has the same variable passed into it.
    auto start = std::chrono::high_resolution_clock::now(); // start time.
    std::sort(sortVec.begin(), sortVec.end()); // sorts the vector.
    runTime(start); // calcultates function run time.

    return sortVec; // returns the new vector.
}

void vecSort(std::vector<std::unique_ptr<int>> &sortVecSmartPtr){ // smart pointer.
    auto start = std::chrono::high_resolution_clock::now(); // start time.
    std::sort(sortVecSmartPtr.begin(), sortVecSmartPtr.end(), [](const std::unique_ptr<int>& a, const std::unique_ptr<int>& b){
        return *a < *b; // comparator compares prt values, rather than memory addresses.
    }); // sorts the vector.
    runTime(start); // calcultates function run time.
}

void vecSort(std::vector<int*> &sortVecPtr){ // regular pointer.
    auto start = std::chrono::high_resolution_clock::now(); // start time.
    std::sort(sortVecPtr.begin(), sortVecPtr.end(), [](int* a, int*b){
        return *a < *b; // comparator compares prt values, rather than memory addresses.
    }); // sorts the vector.

    for(auto ptr : sortVecPtr){ // deletes ptrs after use.
        delete ptr;
    }

    runTime(start); // calcultates function run time.
}

int main(){
    std::vector<int> sortVec(vecSize); // initializes a vector with 10,000 elements. Vector object is on the stack, data in on the heap.
    std::vector<std::unique_ptr<int>> sortVecSmartPtr;
    std::vector<int*> sortVecPtr;
    sortVecSmartPtr.reserve(vecSize);
    sortVecPtr.reserve(vecSize);

    srand(time(nullptr));

    for(int i=0;i<vecSize;i++){ // indexes through the vector, assigning each position a random number.
        sortVec[i] = rand() %vecSize;
        sortVecSmartPtr.push_back(std::make_unique<int>(rand() %vecSize)); // Allocate and store a random number. The pointer is stored in the stack, the data in the heap.
        sortVecPtr.push_back(new int(rand() % vecSize)); // Allocate and store a random number. The pointer is stored in the stack, the data in the heap.
    }

    vecSort(sortVec);
    vecSort(sortVecSmartPtr);
    vecSort(sortVecPtr);

    std::vector<int> returnVec = vecSortReturnVal(sortVec);
} // both sortVec, returnVec, and sortVecPtr are automatically destroyed as they have gone out of scope.


