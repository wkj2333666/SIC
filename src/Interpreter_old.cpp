#include <sstream>
#include <iostream>

#include "Interpreter_old.h"
#include "Exception.h"

void Interpreter::GOTO(int pos, std::ifstream& code) {
    code.seekg(pos);
    // stack_for_call.push_back(pos);
}

void Interpreter::RET(std::ifstream& code) {
    code.seekg(stack_for_call.back());
    stack_for_call.pop_back();
}

std::string Interpreter::CALL(const std::string& function_name, const std::string& args, std::ifstream& code) {
    stack_for_call.push_back(code.tellg());
    GOTO(functions[function_name], code);

    // get function declaration
    std::string function_declaration;
    std::getline(code, function_declaration);

    // split arguments
    std::vector<std::string> split_args;
    std::stringstream ss(args);
    std::string arg;
    while (std::getline(ss, arg, ',')) {
        split_args.push_back(arg);
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
    std::string return_value = interpret(code);

    // remove temporary variables
    for (int i = 0; i < num_of_args; i++) {
        variables.erase(match[i + 1].str());
    }

    return return_value;
}

std::string Interpreter::evaluate(const std::string& expression) {
    return calculator->run(substitute_functions(substitute_variables(expression), code));
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

std::string Interpreter::substitute_functions(const std::string& expression, std::ifstream& code) {
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
            args = substitute_functions(args, code);
            result += CALL(function_name, args, code);
        } else {
            throw UndefinedFunction("Undefined function: " + function_name);
        }
        pos = match.position() + match.length();
    }
    result += expression.substr(pos);
    return result;
}

// std::string Interpreter::execute(std::ifstream& code) {
//     //TODO
// }

std::string Interpreter::interpret(std::ifstream& code) {
    //TODO
    std::string command;
    code >> command;
    if (command == "let") {
        std::string var_name;
        code >> var_name;
        std::string equal_sign;
        std::getline(code, equal_sign, '=');
        std::string expr;
        std::getline(code, expr);
        variables[var_name] = evaluate(expr, code);
    } else if (command == "if") {
        std::string cond;
        std::getline(code, cond);
        int if_start = code.tellg();
        std::string block;
        std::getline(code, block, "end");
    } else if (command == "while") {
        
    } else if (command == "print") {
        std::string expr;
        std::getline(code, expr);
        std::string result = evaluate(expr, code);
        std::cout << result << std::endl;
    } else if (command == "return") {
        std::string expr;
        std::getline(code, expr);
        std::string return_value = evaluate(expr, code);
        RET(code);
        return return_value;
    } else if (command == "EOF") {

    } else {
        throw InvalidCommand("Invalid command: " + command);
    }
}