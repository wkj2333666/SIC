#include <sstream>
#include <iostream>
#include <regex>

#include "Interpreter.h"

std::string LET::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine++;
    std::string var_name;
    std::string var_value;
    std::stringstream sstream(expr);
    
    std::getline(sstream, var_name, '=');
    std::getline(sstream, var_value);
    interpreter->variables[var_name] = interpreter->evaluate(var_value);

    return "";
}

std::string PRINT::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine++;
    std::cout << interpreter->evaluate(expr) << std::endl;

    return "";
}

std::string DEF::execute(Interpreter* const interpreter) const {
    std::regex func_regex(R"(([a-zA-Z_][a-zA-Z0-9_]*)\((.*)\))");
    // [1] for name, [2] for args
    std::smatch func_match;
    std::regex_search(expr, func_match, func_regex);
    
    interpreter->functions[func_match[1]] = LineNumber;
    interpreter->CurrentLine = end + 1;
    return "";
}

std::string END_DEF::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine++;
    return "";
}

std::string IF::execute(Interpreter* const interpreter) const {
    if (std::stoi(interpreter->evaluate(expr))) {
        interpreter->CurrentLine++;
    } else {
        interpreter->CurrentLine = end + 1;
    }

    return "";
}

std::string END_IF::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine++;
    return "";
}

std::string WHILE::execute(Interpreter* const interpreter) const {
    if (std::stoi(interpreter->evaluate(expr))) {
        interpreter->CurrentLine++;
    } else {
        interpreter->CurrentLine = end + 1;
    }

    return "";
}

std::string END_WHILE::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine = begin;
    return "";
}

std::string RET::execute(Interpreter* const interpreter) const {
    std::string return_value = interpreter->evaluate(expr);
    interpreter->CurrentLine = interpreter->stack_for_call.back();
    interpreter->stack_for_call.pop_back();
    return return_value;
}

std::string EXPR::execute(Interpreter* const interpreter) const {
    interpreter->evaluate(expr);
    interpreter->CurrentLine++;
    return "";
}