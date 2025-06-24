#include <iostream>
#include <string>
#include "liams_calculator.hpp"  // Your calculator class header

int main() {
    calculator::calculator calc(std::cout);  // create calculator with debug output to console
    std::string input;

    std::cout << "Enter expressions to calculate, or type 'exit' to quit.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "EXIT") {
            std::cout << "Bye, nerd.\n";
            break;
        }

        try {
            float result = calc.execute(input);
            std::cout << "Result: " << result << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}