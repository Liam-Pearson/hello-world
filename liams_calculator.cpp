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
    
    std::string editableEquation;

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

    if (!current_number.empty()) { // accounts for the last number.
        numbers.push_back(std::stof(current_number));
    }

    editableEquation = equation;

    std::cout << "\n" << equationEater(editableEquation);

    return 0;
}

std::string calculator::calculator::equationEater(std::string equation){

    std::string editableEquation = equation;

    std::vector<float> numbers;
    std::vector<char> operators;

    std::string current_number;

    std::vector<float> tempNumbers; // temp vector for numbers contained in brackets.
    std::vector<char> tempOperators; // temp vector for operators containedin brackets.
    std::string tempEquation;
    std::vector<int> leftRightIndex;

    leftRightIndex = bracketDetect(equation);
    
    tempEquation = equation.substr(leftRightIndex[0]+1, leftRightIndex[1]-2 - leftRightIndex[0]+1);

    for (char c : tempEquation){ // checks all characters of the string.
        if (std::isdigit(c) || c == '.'){ // checks if 'c' is a number.
            current_number += c; // sets the current number string to 'c'.
        }
        else {
            if(!current_number.empty()){ // if current number is not empty, place the current_number into the numbers vector.
                tempNumbers.push_back(std::stof(current_number));
                current_number.clear();
            }

            tempOperators.push_back(c); // place the operator into the operators vector.
        }
    }

    if (!current_number.empty()) { // accounts for the last number.
        tempNumbers.push_back(std::stof(current_number));
    }

    int result = calc(tempNumbers, tempOperators);
    std::string strResult = std::to_string(result);

    editableEquation.erase(leftRightIndex[0],leftRightIndex[1]-leftRightIndex[0]+1); // erase the operator used for the calculation.
    editableEquation.replace(leftRightIndex[0],1,strResult);
    if(leftRightIndex[2]>1){
        editableEquation += ')';
    }

    return editableEquation;
}

std::vector<int> calculator::calculator::bracketDetect(std::string ops){
    int index = 0;
    int leftBracketIndex = 0;
    int rightBracketIndex = 0;
    int bracketCounter = 0;

    std::string operators = ops; // vector containing all operator characters.

    std::vector<int> leftRightIndex; // vector to contain the left and right bracket index.

    for (int i = 0; i < operators.size(); ++i){ // goes through the vector until a closing bracket ')' is found.
        if (operators[i] == '('){
            leftBracketIndex = index;
            std::cout << "\nOpening bracket at operator # " << leftBracketIndex;
            bracketCounter++;
        }
        if (operators[i] == ')'){
            rightBracketIndex = index;
            std::cout << "\nClosing bracket at operator # " << rightBracketIndex;
            break;
        }
        index++;
    }

    // assigns left and right bracket index positions.
    leftRightIndex.push_back(leftBracketIndex);
    leftRightIndex.push_back(rightBracketIndex);
    leftRightIndex.push_back(bracketCounter);

    return leftRightIndex;
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