#include "Calculator.h"
#include <iostream>

void Calculator::clear(std::vector<BaseToken*>& vec) {
    for (auto it = vec.begin(); it != vec.end(); it++) {
        delete *it;
    }
    vec.clear();
}


void Calculator::tokenize(std::string input) {
    tokenizer->tokenize(tokens, input);
    #ifdef DEBUG
    std::cout << "token size: " << tokens.size() << std::endl;
    #endif
}

void Calculator::transform() {
    stack.clear(); // use as op stack;
    postfix.clear();
    for (auto it = tokens.begin(); it != tokens.end(); it++) {
        if ((*it)->getType() == 0) {
            // DataToken
            postfix.push_back((*it));
        } else if ((*it)->getType() == 1) {
            // OpToken
            if (stack.empty() || 
            dynamic_cast<OpToken*>(stack.back())->getPriority()
             < dynamic_cast<OpToken*>(*it)->getPriority())
            {
                stack.push_back((*it));
            } else {
                while (!stack.empty() && 
                dynamic_cast<OpToken*>(stack.back())->getPriority()
                >= dynamic_cast<OpToken*>(*it)->getPriority())
                {
                    postfix.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back((*it));
            }
        }
    }
    while (!stack.empty()) {
        postfix.push_back(stack.back());
        stack.pop_back();
    }
}

DataToken* Calculator::calculate() {
    stack.clear();
    for (auto it = postfix.begin(); it != postfix.end(); it++) {
        #ifdef DEBUG
        std::cout << "Calculating pos:" << it - postfix.begin() << std::endl;
        #endif
        if ((*it)->getType() == 0) {
            // DataToken
            stack.push_back((*it));
        } else if ((*it)->getType() == 1) {
            // OpToken
            #ifdef DEBUG
            std::cout << "Processing op" << std::endl;
            #endif
            DataToken* right = dynamic_cast<DataToken*>(stack.back());
            stack.pop_back();
            DataToken* left = dynamic_cast<DataToken*>(stack.back());
            stack.pop_back();
            #ifdef DEBUG
            std::cout << "Calculating with op: " << std::endl;
            #endif
            stack.push_back(dynamic_cast<OpToken*>(*it)->calc(left, right));
        }
    }
    #ifdef DEBUG
    std::cout << "Returning from calculate()" << std::endl;
    #endif
    return dynamic_cast<DataToken*>(stack.back());
}

void Calculator::run(std::string input) {
    #ifdef DEBUG
    std::cout << "Tokenizing: " << input << std::endl;
    #endif
    tokenize(input);
    #ifdef DEBUG
    std::cout << "Transforming" << std::endl;
    #endif
    transform();
    #ifdef DEBUG
    std::cout << "Calculating" << std::endl;
    #endif
    std::cout << *calculate() << std::endl;
    tokens.clear();
}
