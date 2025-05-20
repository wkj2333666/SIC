#pragma once
#include <unordered_map>
#include <fstream>
#include <regex>

#include "Calculator.h"
#include "Line.h"

class Interpreter {
    Calculator* calculator;
    int CurrentLine;
    // int currentPos;
    std::vector<int> stack_for_call;
    std::vector<Line*> codes;
    // std::vector<int> cstack_for_while;

    std::unordered_map<std::string, int> functions;
    std::unordered_map<std::string, std::string> variables;

    std::regex regex_for_variable;
    std::regex regex_for_function;
    std::regex regex_for_param_list;

    std::string evaluate(const std::string& expression);
        std::string substitute_variables(const std::string& expression);
        std::string substitute_functions(const std::string& expression);
        std::string CALL(const std::string& function_name, const std::string& args);
        // std::vector<std::string> split_args(const std::string& args);
    
    void parse(std::fstream& code_file);
        void parse_if();
        void parse_while();
        void parse_def();
public:
    Interpreter():
        calculator(new Calculator()),
        CurrentLine(0),
        stack_for_call(),
        codes(),
        functions(),
        variables(),
        regex_for_variable(R"([a-zA-Z_][a-zA-Z0-9_]*)(?!\()"),
        regex_for_function(R"(([a-zA-Z_][a-zA-Z0-9_]*)\((.*)\))"),
        // [1] for function name, [2] for arguments
        regex_for_param_list(R"(([a-zA-Z_][a-zA-Z0-9_]*)\s*(?=,|\)))")
    {}
    ~Interpreter() {
        delete calculator;
        for (auto line : codes) {
            delete line;
        }
    }
    void interpret();

    friend class LET;
    friend class PRINT;
    friend class DEF;
    friend class END_DEF;
    friend class IF;
    friend class END_IF;
    friend class WHILE;
    friend class END_WHILE;
    friend class RET;
    friend class EXPR;
};