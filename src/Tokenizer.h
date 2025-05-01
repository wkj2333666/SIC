#pragma once
#include "Token.h"
#include <vector>

class Tokenizer {
    std::vector<std::string> op;
    std::vector<std::string> digit;
public:
    Tokenizer(): op({"+", "-", "*", "/"}), 
    //    , "(", ")", "{", "}", "[", "]", "=", ":", ",", ".", "!", "&&", "||", "<", ">", "<=", ">=", "==", "!="}) {}
        digit({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."}) {}
    ~Tokenizer() = default;
    void tokenize(std::vector<BaseToken*>& tokens, std::string input);

    bool isOperator(std::string s);
    bool isDigit(std::string s);

    std::string getDigit(std::string s, int& pos);
    std::string getOperator(std::string s, int& pos);
};