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

    if (!current_number.empty()) { // accounts for the last number.
        numbers.push_back(std::stof(current_number));
    }

    std::cout << "\nNumbers: ";
    for (float n : numbers) std::cout << n << " ";
    std::cout << "\nOperators: ";
    for (char op : operators) std::cout << op << " ";
    std::cout << std::endl;

    int opIndex = 0;
    float result = 0;
    int staticOpIndex=0;

    std::vector<char> staticOperators = {'/', '*', '+', '-'}; // BEDMAS

    for(char c : staticOperators){
        for (char c : operators){
            if(operators[opIndex] == staticOperators[staticOpIndex]){
                switch(operators[opIndex]){
                    case '*':
                        result = multiply(numbers[opIndex], numbers[opIndex + 1]);
                        std::cout << "\nMultiplying: " << numbers[opIndex] << " " << numbers[opIndex+1];
                        break;
                    case '/':
                        result = divide(numbers[opIndex], numbers[opIndex + 1]);
                        std::cout << "\nDividing: " << numbers[opIndex] << " " << numbers[opIndex+1];
                        break;
                    case '+':
                        result = add(numbers[opIndex], numbers[opIndex + 1]);
                        std::cout << "\nAdding: " << numbers[opIndex] << " " << numbers[opIndex+1];
                        break;
                    case '-':
                        result = subtract(numbers[opIndex], numbers[opIndex + 1]); 
                        std::cout << "\nSubtracting: " << numbers[opIndex] << " " << numbers[opIndex+1];
                        break;
                    default:
                        std::cerr << "Unknown operator encountered: " << operators[opIndex] << '\n';
                        break;
                }

                numbers.erase(numbers.begin() + opIndex, numbers.begin() + opIndex + 2);
                numbers.insert(numbers.begin() + opIndex, result);
                operators.erase(operators.begin() + opIndex);

                result = 0;
            }
            else{
                opIndex++;
            }

            std::cout << "\n" << result;
            std::cout << "\nopIndex: " << opIndex;
            
            result = 0;
            
            std::cout << "\nNumbers: ";
            for (float n : numbers) std::cout << n << " ";
            std::cout << "\nOperators: ";
            for (char op : operators) std::cout << op << " ";
            std::cout << std::endl;            
        }
        staticOpIndex++;
        opIndex=0;
    }

    std::cout << "\nNumbers: ";
    for (float n : numbers) std::cout << n << " ";
    std::cout << "\nOperators: ";
    for (char op : operators) std::cout << op << " ";
    std::cout << std::endl;

    return 0;
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
    calculator::calculator calc (std::cout);

    std::string input = "12+34*895/90*2+95";
    float result = calc.execute(input);
}