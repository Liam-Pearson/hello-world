#include "liams_calculator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

calculator::calculator::calculator(std::ostream& debug_log):debug_log(debug_log), memory (0.0f){

}

float calculator::calculator::execute(std::string const equation){

    std::vector<float> numbers;
    std::vector<char> operators;

    std::string current_number;

    for (char c : equation){ // checks all characters of the string.
        if (std::isdigit(c) || c == '.'){ // checks if 'c' is a number.
            current_number += c; // sets the current number string to 'c'.
        }
        else {
            if(!current_number.empty()){ // if current number is not empty, place the current_number into the numbers vector.
                numbers.push_back(std::stof(current_number));
                current_number.clear();
            }

            operators.push_back(c); // place the operator into the operators vector.
        }
    }

    int opIndex = 0;
    for (char c : operators){
        if (c == '('){
            
        }
    }

    if (!current_number.empty()) { // accounts for the last number.
        numbers.push_back(std::stof(current_number));
    }

    numbers[0] = calc(numbers, operators);

    std::cout << "\nAns: " << numbers[0];
    
    return 0;
}

float calculator::calculator::calc(std::vector<float> nums, std::vector<char> ops){
    int opIndex = 0; // index posiiton of the current operator in the operators vector.
    float result = 0; // result of operation performed.
    int staticOpIndex=0; // index of the BEDMAS operator to be performed.

    std::vector<float> numbers = nums;
    std::vector<char> operators = ops;

    std::vector<char> staticOperators = {'/', '*', '+', '-'}; // BEDMAS. Changing the order of this array changes the order of operations.

    for(char c : staticOperators){ // indexes through all BEDMAS operators.
        for (char c : operators){ // indexes through all operators in the operator vector.
            if(operators[opIndex] == staticOperators[staticOpIndex]){ // if the operator at the current index is also equal to the current most important operator (BEDMADS). perform the switch cases.
                switch(operators[opIndex]){
                    case '*':
                        result = multiply(numbers[opIndex], numbers[opIndex + 1]);
                        std::cout << "\nMultiplying: " << numbers[opIndex] << " by " << numbers[opIndex+1];
                        std::cout << "\nResult: " << result;
                        break;
                    case '/':
                        result = divide(numbers[opIndex], numbers[opIndex + 1]);
                        std::cout << "\nDividing: " << numbers[opIndex] << " by " << numbers[opIndex+1];
                        std::cout << "\nResult: " << result;
                        break;
                    case '+':
                        result = add(numbers[opIndex], numbers[opIndex + 1]);
                        std::cout << "\nAdding: " << numbers[opIndex] << " to " << numbers[opIndex+1];
                        std::cout << "\nResult: " << result;
                        break;
                    case '-':
                        result = subtract(numbers[opIndex], numbers[opIndex + 1]); 
                        std::cout << "\nSubtracting: " << numbers[opIndex+1] << " from " << numbers[opIndex];
                        std::cout << "\nResult: " << result;
                        break;
                    default:
                        std::cerr << "Unknown operator encountered: " << operators[opIndex] << '\n';
                        break;
                }

                numbers.erase(numbers.begin() + opIndex, numbers.begin() + opIndex + 2); // erase the two numbers used to perform the operartion.
                numbers.insert(numbers.begin() + opIndex, result); // insert the result of the calculation into the  left most position that had a value erased.
                operators.erase(operators.begin() + opIndex); // erase the operator used for the calculation.

                result = 0; // reset the result value for the next calculation.
                std::cout << "\nNumbers: ";
                for (float n : numbers) std::cout << n << " ";
                std::cout << "\nOperators: ";
                for (char op : operators) std::cout << op << " ";
            }
            else{
                opIndex++; // if the current operator is not the most important operator, increment forwards until most important operator is found, or if end of vector has been reached.
            }

            //std::cout << "\n" << result;
            //std::cout << "\nopIndex: " << opIndex;
            
            result = 0; // reset the result value to prepare for the next calculation.       
        }

        staticOpIndex++; // increment forwards the most important operator (BEDMAS).
        opIndex=0; // reset the operator index.
    }

    return numbers[0];
}

float calculator::calculator::add(float const a, float const b){
    return a+b;
}

float calculator::calculator::subtract(float const a, float const b){
    return a-b;
}

float calculator::calculator::divide(float const a, float const b){
    return a/b;
}

float calculator::calculator::multiply(float const a, float const b){
    return a*b;
}

float calculator::calculator::pow(float const base, float const exp){
    return 0;
}

float calculator::calculator::fact_i(int const n){
    return 0;
} // iterative factorial

float calculator::calculator::fact_r(int const n){
    return 0;
} // recursive factorial

int main(){
    calculator::calculator myCalc(std::cout);
    std::string input;
    std::cout << "Enter a math equation (e.g., 3+4*2): ";
    std::getline(std::cin, input);

    float result = myCalc.execute(input);

    return 0;
}