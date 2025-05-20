#include "Interpreter.h"

std::string Interpreter::CALL(const std::string& function_name, const std::string& args) {
    stack_for_call.push_back(CurrentLine);
    CurrentLine = functions[function_name];

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