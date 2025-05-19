#pragma once
#include <unordered_map>
#include <fstream>
#include <regex>

#include "Calculator.h"

enum Command{
    IF,
    ELSE,
    WHILE,
    END,
    LET,
    DEF,
    RET,
};

class Interpreter {
    Calculator* calculator;
    // int currentPos;
    std::vector<int> stack_for_call;
    // std::vector<int> cstack_for_while;

    std::unordered_map<std::string, int> functions;
    std::unordered_map<std::string, std::string> variables;

    std::regex regex_for_variable;
    std::regex regex_for_function;
    std::regex regex_for_param_list;

    std::string evaluate(const std::string& expression, std::ifstream& code);
        std::string substitute_variables(const std::string& expression);
        std::string substitute_functions(const std::string& expression, std::ifstream& code);
            // std::vector<std::string> split_args(const std::string& args);

    void GOTO(int pos, std::ifstream& code);
    void RET(std::ifstream& code);
    std::string CALL(const std::string& function_name, const std::string& args, std::ifstream& code);
public:
    Interpreter(): 
        calculator(new Calculator()),
        stack_for_call(),
        functions(),
        variables(),
        regex_for_variable(R"([a-zA-Z_][a-zA-Z0-9_]*)(?!\()"),
        regex_for_function(R"(([a-zA-Z_][a-zA-Z0-9_]*)\((.*)\))"),
        // [1] for function name, [2] for arguments
        regex_for_param_list(R"(([a-zA-Z_][a-zA-Z0-9_]*)\s*(?=,|\)))")
    {}
    ~Interpreter() {delete calculator;}

    // std::string execute(std::ifstream& code);
    std::string interpret(std::ifstream& code);
};