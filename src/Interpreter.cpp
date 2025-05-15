#include "Interpreter.h"
#include "Exception.h"

void Interpreter::GO2(int pos, std::ifstream& code) {
    code.seekg(pos);
    stack_for_call.push_back(pos);
}

void Interpreter::RET(std::ifstream& code) {
    code.seekg(stack_for_call.back());
    stack_for_call.pop_back();
}

std::string Interpreter::evaluate(const std::string& expression) {
    return calculator->run(substitute_functions(substitute_variables(expression)));
}

std::string Interpreter::substitute_variables(const std::string& expression) {
    std::sregex_iterator it(expression.begin(), expression.end(), regex_for_variable);
    std::sregex_iterator end;
    size_t pos = 0;
    std::string result;

    for (; it != end; ++it) {
        std::smatch match = *it;
        result += match.prefix().str();
        std::string var_name = match[0].str();
        if (variables.find(var_name) != variables.end()) {
            result += variables[var_name]->toString();
        } else {
            throw UndefinedVariable("Undefined variable: " + var_name);
        }
        pos = match.position() + match.length();
    }
    result += expression.substr(pos);
    return result;
}

std::string Interpreter::substitute_functions(const std::string& expression) {
    //TODO
}