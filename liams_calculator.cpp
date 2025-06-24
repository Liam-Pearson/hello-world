#include "liams_calculator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <utility>
#include <cmath>

calculator::calculator::calculator(std::ostream& debug_log):debug_log(debug_log), memory (0.0f){

}

float calculator::calculator::execute(std::string const equation){

    std::string cleanedEquation = equation;

    int i =0;

    if(hasSpaces(cleanedEquation) == false && consecutiveOperators(cleanedEquation) == false && bracketsMatch(cleanedEquation) == true && equationLeadEndOpCleanup(cleanedEquation) == true && hasInvalidLeadingFactorial(cleanedEquation) == false){
        cleanedEquation = wrapInBrackets(cleanedEquation);
        while(containsOperator(cleanedEquation) == true && i < 100 ){
            std::cout << "\nEquation: " << cleanedEquation;
            numBeforeAfter(cleanedEquation, findInnermostBrackets(cleanedEquation));
            cleanedEquation = replacement(evaluateExpressionAsString(extractSubstring(cleanedEquation, findInnermostBrackets(cleanedEquation))),cleanedEquation, findInnermostBrackets(cleanedEquation));
            cleanedEquation = insertMultiplicationAroundBrackets(cleanedEquation, numBeforeAfter(cleanedEquation, findInnermostBrackets(cleanedEquation)), findInnermostBrackets(cleanedEquation));
            i++;
        }
    }
 
    return 0;
}

bool calculator::calculator::hasSpaces(const std::string equation) {
    for (char c : equation) {
        if (c == ' ') {
            std::cout << "\nEquation cannot have spaces.";
            return true;
        }
    }
    return false;
}

bool calculator::calculator::containsOperator(const std::string equation) { // checks if the equation contains any operators.
    for (char c : equation) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            return true;  // Found an operator
        }
    }

    std::cout << "\nNo operators found. Equation solved.";
    
    return false;  // No operator found
}

bool calculator::calculator::consecutiveOperators(std::string const equation){ // checks if there are consecutive operators.
    bool condition = false;

    std::string operators = "+-*/";

    for (size_t i = 1; i < equation.size(); ++i) {
        if (operators.find(equation[i]) != std::string::npos &&
            operators.find(equation[i - 1]) != std::string::npos) {
            condition = true; // Found consecutive operators
            std::cout << "\nEquation cannot have consecutive operators (++,-+, etc.).";
        }
    }

    return condition;
}

bool calculator::calculator::equationLeadEndOpCleanup(std::string const equation){ // cleans the equation of any leading or ending double or greater operators.

    std::string operators = "+-*/^"; // list of operators to be removed if the equation contains them at the start or finish.
    size_t start = 0;
    size_t end = equation.length();

    // Remove leading operators
    while (start < end && operators.find(equation[start]) != std::string::npos) {
        start++;
        std::cout << "\nLeading operator present. Equation is invalid.";
        return false;
    }

    // Remove trailing operators
    while (end > start && operators.find(equation[end - 1]) != std::string::npos) {
        end--;
        std::cout << "\nTrailing operator present. Equation is invalid.";
        return false;
    }

    return true;
}

bool calculator::calculator::hasInvalidLeadingFactorial(const std::string equation) {
    for (size_t i = 1; i < equation.length(); ++i) {
        if (equation[i - 1] == '!' && (std::isdigit(equation[i]) || equation[i] == '.')) {
            std::cout << "\nInvalid: '!' appears before number at position " << i;
            return true;
        }
    }
    return false;
}

std::string calculator::calculator::wrapInBrackets(const std::string equation) {
    return "(" + equation + ")";
}


bool calculator::calculator::bracketsMatch(std::string const equation){ // checks if the number of opening brackets matches the number of closing brackets.
    int openCount = 0;
    int closeCount = 0;

    for (char c : equation) {
        if (c == '(') openCount++;
        else if (c == ')') closeCount++;
    }

    if(openCount != closeCount){
        std::cout << "\nEquation closing and opening bracket count do not match.";
    }

    // Return true if the number of closing and opening brackets match.
    return openCount == closeCount;
}

std::vector<int> calculator::calculator::findInnermostBrackets(const std::string equation) { // finds the innermost set of brackets.
    int openBracket = -1;
    int closedBracket = -1;

    for (int i = 0; i < equation.size(); ++i) {
        if (equation[i] == '(') {
            openBracket = i;  // store the position of the latest '('
        } else if (equation[i] == ')') { // if ')' is found, break out.
            closedBracket = i;
            break;
        }
    }

    //std::cout << "\nBrackets are at: " << openBracket << " " << closedBracket;

    return {openBracket, closedBracket};
}

std::vector<bool> calculator::calculator::numBeforeAfter(std::string equation, std::vector<int> bracketPos){ // checks if there are numbers immediately before or after a set of brackets.

    std::vector<bool> numCheck(4, false);

    if (std::isdigit(equation[bracketPos[0]-1]) == 1 || equation[bracketPos[0] - 1] == '!') {
        numCheck[0] = true;
        //std::cout<< "\nMultiplier before brackets.";
    }

    if (std::isdigit(equation[bracketPos[1]+1])) {
        numCheck[1] = true;
        //std::cout<< "\nMultiplier after brackets.";
    }

    if (equation[bracketPos[1]+1] == '!') {
        numCheck[3] = true;
        //std::cout<< "\nFactorial after brackets.";
    }

    if (numCheck[0] == true && numCheck[1] == true){
        numCheck[2] = true;
    }
    else {
        numCheck[2] = false;
    }

    return numCheck;
}

std::string calculator::calculator::extractSubstring(const std::string equation, std::vector<int> bracketsPos) { // extracts the equation inside of brackets.

    int start = bracketsPos[0]+1;
    int end = bracketsPos[1]-1;

    if (start < 0) start = 0;
    if (end >= (int)equation.size()) end = equation.size() - 1;
    if (start > end) return "";

    std::cout << "\n" << equation.substr(start, end - start + 1);

    return equation.substr(start, end - start + 1);
}

std::string calculator::calculator::evaluateExpressionAsString(const std::string equation) {
    float currentNum = 0.;
    float lastValue = 0;
    float result = 0;
    char lastOp = '+';
    int i = 0;

    while (i < equation.length()) {
        if (std::isspace(equation[i])) {
            i++;
            continue;
        }

        if (std::isdigit(equation[i]) || equation[i] == '.') {
            std::string numStr;
            while (i < equation.length() && (std::isdigit(equation[i]) || equation[i] == '.')) {
                numStr += equation[i++];
            }

            currentNum = std::stof(numStr);
            
            // Check for factorial
            if (i < equation.length() && equation[i] == '!') {
                if (currentNum < 0 || std::floor(currentNum) != currentNum) {
                    throw std::runtime_error("Factorial only defined for non-negative integers");
                }

                currentNum = fact_i(static_cast<int>(currentNum));
                ++i;
            }

            if (lastOp == '*') {
                lastValue = multiply(lastValue, currentNum);
            } else if (lastOp == '/') {
                if (currentNum == 0) throw std::runtime_error("Division by zero");
                lastValue = divide(lastValue, currentNum);
            } else if (lastOp == '+') {
                result = add(result, lastValue);
                lastValue = currentNum;
            } else if (lastOp == '-') {
                lastValue = subtract(lastValue, currentNum);
            } else if (lastOp == '^'){
                lastValue = pow(lastValue, currentNum);
            }
        } else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '^') {
            lastOp = equation[i];
            i++;
        } else {
            throw std::runtime_error("Invalid character in expression");
        }
    }

    result = add(result, lastValue);

    // Convert result to string
    std::ostringstream oss;
    oss << result;

    std::cout << "\nCalculation result: " << oss.str();
    return oss.str();
}

std::string calculator::calculator::replacement(std::string result, std::string equation, std::vector<int> bracketPos){
    if (bracketPos[0] < 0 || bracketPos[1] < bracketPos[0] || bracketPos[1] >= equation.size() || equation[bracketPos[0]] != '(' || equation[bracketPos[1]] != ')') {
        std::cerr << "\nInvalid bracket positions.";
        return equation;
    }

    std::string updated = equation.substr(0, bracketPos[0] + 1) + result + equation.substr(bracketPos[1]); // include ')'

    std::cout << "\nUpdated equation: " << updated;
    return updated;
}

std::string calculator::calculator::insertMultiplicationAroundBrackets(std::string equation, std::vector<bool> bracketBool, std::vector<int> bracketPos){
    std::string updated = equation;

    if (bracketBool.size() < 3 || bracketPos.size() < 2) {
        std::cout << "\nInvalid input sizes.";
        return updated;
    }
    
    if (bracketBool[2]) {
        // Replace both brackets with '*', keep both characters
        updated[bracketPos[0]] = '*';
        updated[bracketPos[1]] = '*';
        //std::cout << "\nReplaced both brackets with '*': " << updated << std::endl;
        return updated;
    }

    if (bracketBool[0]) {
        // Replace left bracket with '*', delete right bracket
        updated[bracketPos[0]] = '*';
        // Remove right bracket at index 'right'
        updated.erase(bracketPos[1], 1);
        //std::cout << "\nReplaced left bracket with '*', deleted right bracket: " << updated << std::endl;
        return updated;
    }

    if (bracketBool[3]) {
        updated.erase(bracketPos[1], 1);
        updated.erase(bracketPos[0], 1);
    }

    if (bracketBool[1]) {
        // Replace right bracket with '*', delete left bracket
        updated[bracketPos[1]] = '*';
        // Remove left bracket at index 'left'
        updated.erase(bracketPos[0], 1);
        //std::cout << "\nReplaced right bracket with '*', deleted left bracket: " << updated << std::endl;
        return updated;
    }

    // If none true, return original
    std::cout << "\nNo replacements done. Equation: " << updated << std::endl;
    return updated;
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
    return std::pow(base, exp);
}

float calculator::calculator::fact_i(int const n){
    if (n < 0) {
        throw std::invalid_argument("\nNegative factorials are invalid.");
    }

    float result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
} // iterative factorial

float calculator::calculator::fact_r(int const n){
    if (n < 0) {
        throw std::invalid_argument("Negative factorial not defined.");
    }

    if (n == 0 || n == 1) {
        return 1;
    }

    return n * fact_r(n - 1);
} // recursive factorial

int main(){
  std::string equation = "1+2(2^2+6!((1+4)!+7*8/9)/500)";

  calculator::calculator calc(std::cout);
  calc.execute(equation);
}