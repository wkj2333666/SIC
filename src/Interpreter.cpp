#include "Interpreter.h"
#include "Exception.h"

std::string Interpreter::CALL(const std::string& function_name, const std::string& args) {
    stack_for_call.push_back(CurrentLine);
    CurrentLine = functions[function_name];

    // get function declaration
    std::string function_declaration = codes[CurrentLine].expr;

    // split arguments
    std::vector<std::string> split_args;
    {
        std::smatch match;
        std::regex_search(function_declaration, match, regex_for_param_list);
        for (int i = 1; i < match.size(); i++) {
            split_args.push_back(match[i].str());
        }
    }
    
    // get function params
    int num_of_args = args.size();
    std::smatch match;
    std::regex_search(function_declaration, match, regex_for_param_list);
    if (match.size() != num_of_args + 1) {throw InvalidArguments("Invalid number of arguments for function " + function_name);}
    for (int i = 0; i < num_of_args; i++) {
        variables[match[i + 1].str()] = calculator->run(split_args[i]);
    }

    // execute function body
    CurrentLine++; // enter function body
    std::string return_value;
    while ((return_value = codes[CurrentLine].execute(this)) != ""){}

    // remove temporary variables
    for (int i = 0; i < num_of_args; i++) {
        variables.erase(match[i + 1].str());
    }

    return return_value;
}

std::string Interpreter::evaluate(const std::string& expression) {
    for (int i=0; i<expression.size(); i++) {
        if (!std::isspace(expression[i]))
            return calculator->run(substitute_functions(substitute_variables(expression)));
    }
    return " "; // differ from ""
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
            result += variables[var_name];
        } else {
            throw UndefinedVariable("Undefined variable: " + var_name);
        }
        pos = match.position() + match.length();
    }
    result += expression.substr(pos);
    return result;
}

std::string Interpreter::substitute_functions(const std::string& expression) {
    std::sregex_iterator it(expression.begin(), expression.end(), regex_for_function);
    std::sregex_iterator end;
    size_t pos = 0;
    std::string result;

    for (; it != end; ++it) {
        std::smatch match = *it;
        result += match.prefix().str();
        std::string function_name = match[1].str();
        std::string args = match[2].str();
        if (functions.find(function_name) != functions.end()) {
            args = substitute_functions(args);
            result += CALL(function_name, args);
        } else {
            throw UndefinedFunction("Undefined function: " + function_name);
        }
        pos = match.position() + match.length();
    }
    result += expression.substr(pos);
    return result;
}
