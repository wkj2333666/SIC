#include <unordered_map>
#include <fstream>

#include "Calculator.h"

class Interpreter {
    Calculator* calculator;
    // int currentPos;
    std::vector<int> stack_for_call;
    std::unordered_map<std::string, int> functions;
    std::unordered_map<std::string, TYPE> variables;

    std::string evaluate(const std::string& expresion);
    void GO2(int pos, std::ifstream& code);
    void RET(std::ifstream& code);
public:
    Interpreter(): calculator(new Calculator()), stack_for_call(), functions(), variables() {}
    ~Interpreter() { delete calculator; }

    void interpret(std::ifstream& code);
};