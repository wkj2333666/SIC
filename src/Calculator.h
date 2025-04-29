#pragma once 
#include "Tokenizer.h"

class Calculator {
    std::vector<BaseToken*> tokens; // ownership
    std::vector<BaseToken*> postfix;// ownership
    std::vector<BaseToken*> stack;  // no ownership
    Tokenizer* tokenizer;
public:
    Calculator(): tokens(), postfix(), stack(), tokenizer(new Tokenizer()) {}
    ~Calculator() {
        delete tokenizer;
    }
    void tokenize(std::string input);
    void transform();
    DataToken* calculate();
    void run(std::string input);
    void clear(std::vector<BaseToken*>& vec);
};