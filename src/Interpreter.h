#include <unordered_map>
#include <fstream>
#include <regex>

#include "Calculator.h"

class Interpreter {
    Calculator* calculator;
    // int currentPos;
    std::vector<int> stack_for_call;
    std::unordered_map<std::string, int> functions;
    std::unordered_map<std::string, DataToken*> variables;
    // ownership

    std::regex regex_for_variable;
    std::regex regex_for_function;

    std::string substitute_variables(const std::string& expression);
    std::string substitute_functions(const std::string& expression);
    std::string evaluate(const std::string& expression);
    void GO2(int pos, std::ifstream& code);
    void RET(std::ifstream& code);
public:
    Interpreter(): 
        calculator(new Calculator()),
        stack_for_call(),
        functions(),
        variables(),
        regex_for_variable(R"([a-zA-Z0-9_]+)(?!\()"),
        regex_for_function(R"(([a-zA-Z0-9_]+)\((.*)\))")
        // [1] for function name, [2] for arguments
    {}
    ~Interpreter() { 
        delete calculator; 
        for (auto it = variables.begin(); it != variables.end(); ++it) {
            delete it->second;
        }
    }

    void interpret(std::ifstream& code);
};