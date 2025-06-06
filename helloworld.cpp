#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int sort()
{
    std::vector<int> sortVec {121,12,4673,540,5,66,75467,8,9,33636,2,3663,74,23,336,2574,25};

    int vecEls= sortVec.size(); // size of vector.
    int largest = sortVec[0]; // initalizes largest number to the first position of the vector.
    int sortCount = 0; // starting position to sort from.

    for(int i =0; i<vecEls; i++){ // applies sorting algorithm to entire vector.
        for (int i = sortCount; i < vecEls; i++) { // sorts for the largest number from the first position to the last position of the vector.
            if((i+1) < vecEls) { // stops from doing the sorting comparison from outside the vector length (for last position only really).
                if(sortVec[i+1] - largest > 0) { // if greater than 0, largest current number has been found.
                    largest=sortVec[i+1]; // assigns largest number
                    sortVec[i+1] = sortVec[sortCount]; // takes the current first number position and moves it to the position of the largest number in the vector.
                    sortVec[sortCount] = largest; // move the current largest number to the first position of the vector.
                }
            }
        }
        sortCount++; // increments the starting position of the vector.
        largest = sortVec[sortCount]; // sets the new largest number starting point to the new starting positon of the vector.
    }

    for(int i =0; i<vecEls; i++){
        std::cout << "\n Vec:" << sortVec[i];
    }

    std::sort(sortVec.begin(), sortVec.end());

    for(int i : sortVec){
        std::cout << "\n" << i;
    }

    return 0;
}

int main()
{
    std::vector<std::string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const std::string& word : msg) {
        std::cout << word << " ";
    }
    //std::cout << std::endl;

    int largestVar = sort();
}

