#include <iostream>
#include <unordered_map>
#include <functional>

#include "Calculator.h"

std::unordered_map<std::string, TYPE> variables;
std::unordered_map<std::string, std::function<TYPE(std::vector<TYPE>)>> functions;

int main() {
    Calculator calculator;
    std::string input;
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, input);
        if (std::cin.eof()) {
            return 0;
        }

        #ifdef DEBUG
        std::cout << "Running calculator" << std::endl;
        #endif
        try {
            calculator.run(input);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            calculator.clear();
        }
    }
    return 0;
}