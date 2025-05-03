#pragma once
#include <vector>

#include "Token.h"

class Tokenizer {
    std::vector<std::string> op;
    std::vector<std::string> digit;
    int LoverR;
public:
    Tokenizer(): op({"+", "-", "*", "/", "^", "%"}), 
    //    , "(", ")", "{", "}", "[", "]", "=", ":", ",", ".", "!", "&&", "||", "<", ">", "<=", ">=", "==", "!="}) {}
        digit({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."}),
        LoverR(0){}
    ~Tokenizer() = default;
    void tokenize(std::vector<std::shared_ptr<BaseToken>>& tokens, const std::string& input);

    bool isOperator(const std::string& s) const;
    bool isDigit(const std::string& s) const;
    void skipSpace(std::vector<std::shared_ptr<BaseToken>>& tokens, const std::string& s, int& pos);

    std::string getDigit(const std::string& s, int& pos)const;
    std::string getOperator(const std::string& s, int& pos)const;
};