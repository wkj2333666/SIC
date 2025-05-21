#include <iostream>
#include <fstream>

#include "Interpreter.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

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
    catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        file.close();
        return 1;
    }
    file.close();
    return 0;
}