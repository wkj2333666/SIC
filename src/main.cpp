#include <iostream>
#include <fstream>

#include "Interpreter.h"
#include "Exception.h"

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage:\n" << argv[0] << " <filename>\n\tRun a Sic script." << std::endl;
        std::cerr << argv[0] << "\n\tRun in terminal calculator mode." << std::endl;
        return 1;
    }
    if (argc == 2) {
        std::fstream file;
        file.open(argv[1], std::ios_base::in);
        if (!file.is_open()) {
            std::cerr << "Error: could not open file " << argv[1] << std::endl;
        }
        Interpreter interpreter;
        #ifdef iDEBUG
        std::cout << "Initialized." << std::endl;
        #endif

        try {interpreter.interpret(file);}
        catch (SyntaxError &e) {
            std::cerr << e.what() << std::endl;
            file.close();
            return 1;
        }
        file.close();
    } else {
        Calculator calculator;
        std::string input;
        while (true) {
            std::cout << ">>> ";
            std::getline(std::cin, input);
            if (std::cin.eof()) {
                return 0;
            }
            try {
                std::cout << calculator.run(input) << std::endl;
            } catch (const CalcError &e) {
                std::cerr << e.what() << std::endl;
                calculator.clear();
            }
        }
    }
    return 0;
}