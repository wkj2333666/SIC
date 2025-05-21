#include <sstream>
#include <iostream>
#include <regex>

#include "Interpreter.h"

std::string LET::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine++;
    std::string var_name_buffer;
    std::string var_name;
    std::string var_value;
    std::stringstream sstream(expr);
    
    std::getline(sstream, var_name_buffer, '=');
    std::getline(sstream, var_value);
    for (char c : var_name_buffer) {
        if (std::isspace(c)) continue;
        var_name += c;
    }
    interpreter->variables[var_name] = interpreter->evaluate(var_value);

    return "";
}

std::string PRINT::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine++;
    std::cout << interpreter->evaluate(expr) << std::endl;

    return "";
}

std::string DEF::execute(Interpreter* const interpreter) const {
    std::regex func_regex(R"(([a-zA-Z_]\w*)\[(.*)\])");
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
    #ifdef iDEBUG
    std::cout << "Executing RET at line: " << interpreter->CurrentLine + 1<< std::endl;
    std::cout << "expr: " << expr << std::endl;
    #endif
    std::string return_value = interpreter->evaluate(expr);
    #ifdef iDEBUG
    std::cout << "Returning: " << return_value << std::endl;
    std::cout << "stack_for_call size: " << interpreter->stack_for_call.size() << std::endl;
    #endif
    interpreter->CurrentLine = interpreter->stack_for_call.back();
    interpreter->stack_for_call.pop_back();
    #ifdef iDEBUG
    std::cout << "Returning to line: " << interpreter->CurrentLine + 1 << std::endl;
    #endif
    return return_value;
}

std::string EXPR::execute(Interpreter* const interpreter) const {
    interpreter->evaluate(expr);
    interpreter->CurrentLine++;
    return "";
}

std::string CMT::execute(Interpreter* const interpreter) const {
    interpreter->CurrentLine++;
    return "";
}


#ifdef iDEBUG
void LET::show() const {
    std::cout << "Line " << LineNumber + 1 << ": let" << expr << std::endl;
}

void PRINT::show() const {
    std::cout << "Line " << LineNumber + 1 << ": print" << expr << std::endl;
}

void DEF::show() const {
    std::cout << "Line " << LineNumber + 1 << ": def" << expr << std::endl;
}

void END_DEF::show() const {
    std::cout << "Line " << LineNumber + 1 << ": enddef" << expr << std::endl;
}

void IF::show() const {
    std::cout << "Line " << LineNumber + 1 << ": if" << expr << std::endl;
}

void END_IF::show() const {
    std::cout << "Line " << LineNumber + 1 << ": endif" << expr << std::endl;
}

void WHILE::show() const {
    std::cout << "Line " << LineNumber + 1 << ": while" << expr << std::endl;
}

void END_WHILE::show() const {
    std::cout << "Line " << LineNumber + 1 << ": endwhile" << expr << std::endl;
}

void RET::show() const {
    std::cout << "Line " << LineNumber + 1 << ": return" << expr << std::endl;
}

void EXPR::show() const {
    std::cout << "Line " << LineNumber + 1 << ": " << expr << std::endl;
}

void CMT::show() const {
    std::cout << "Line " << LineNumber + 1 << ": #" << expr << std::endl;
}
#endif