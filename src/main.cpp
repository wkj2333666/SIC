#include "Calculator.h"
#include <iostream>

int main() {
    Calculator calculator;
    std::string input;
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, input);
        #ifdef DEBUG
        std::cout << "Running calculator" << std::endl;
        #endif
        calculator.run(input);
    }
    return 0;
}