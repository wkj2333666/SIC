#include <sstream>
#include <iostream>

#include "Interpreter.h"

std::string LET::execute(Interpreter* interpreter) {
    interpreter->CurrentLine++;
    std::string var_name;
    std::string var_value;
    std::stringstream sstream(expr);
    
    std::getline(sstream, var_name, '=');
    std::getline(sstream, var_value);
    interpreter->variables[var_name] = interpreter->evaluate(var_value);

    return "";
}

std::string PRINT::execute(Interpreter* interpreter) {
    interpreter->CurrentLine++;
    std::cout << interpreter->evaluate(expr) << std::endl;

    return "";
}

std::string DEF::execute(Interpreter* interpreter) {
    interpreter->functions[func_name] = LineNumber;
    interpreter->CurrentLine = end + 1;
    return "";
}

std::string END_DEF::execute(Interpreter* interpreter) {
    interpreter->CurrentLine++;
    return "";
}

std::string IF::execute(Interpreter* interpreter) {
    if (std::stoi(interpreter->evaluate(expr))) {
        interpreter->CurrentLine++;
    } else {
        interpreter->CurrentLine = end + 1;
    }

    return "";
}

std::string END_IF::execute(Interpreter* interpreter) {
    interpreter->CurrentLine++;
    return "";
}

std::string WHILE::execute(Interpreter* interpreter) {
    if (std::stoi(interpreter->evaluate(expr))) {
        interpreter->CurrentLine++;
    } else {
        interpreter->CurrentLine = end + 1;
    }

    return "";
}

std::string END_WHILE::execute(Interpreter* interpreter) {
    interpreter->CurrentLine = begin;
    return "";
}

std::string RET::execute(Interpreter* interpreter) {
    std::string return_value = interpreter->evaluate(expr);
    interpreter->CurrentLine = interpreter->stack_for_call.back();
    interpreter->stack_for_call.pop_back();
    return return_value;
}

std::string EXPR::execute(Interpreter* interpreter) {
    interpreter->evaluate(expr);
    interpreter->CurrentLine++;
    return "";
}