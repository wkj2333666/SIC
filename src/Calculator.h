#pragma once 
#include "Tokenizer.h"

class Calculator {
    std::vector<std::shared_ptr<BaseToken>> tokens; 
    std::vector<std::shared_ptr<BaseToken>> postfix;
    std::vector<std::shared_ptr<BaseToken>> stack;
    Tokenizer* tokenizer;

    void tokenize(const std::string& input);
    void transform();
    std::shared_ptr<DataToken> calculate();
    void pop_until_LPAR();
public:
    Calculator(): tokens(), postfix(), stack(), tokenizer(new Tokenizer()) {}
    ~Calculator() {
        delete tokenizer;
    }
    void run(const std::string& input);
    void clear();
};