#include "Calculator.h"

#include <iostream>
#include <unordered_map>
#include <functional>

#include "Exception.h"

extern std::unordered_map<std::string, TYPE> variables;
extern std::unordered_map<std::string, std::function<TYPE(std::vector<TYPE>)>> functions;

void Calculator::clear() {
    tokens.clear();
    postfix.clear();
    stack.clear();
}

void Calculator::tokenize(const std::string& input) {
    tokenizer->tokenize(tokens, input);
    #ifdef DEBUG
    std::cout << "Got tokens: ";
    for (auto it = tokens.begin(); it != tokens.end(); it++) {
        std::cout << (*it)->toString() + ' ';
    }
    std::cout << std::endl;
    #endif
}

void Calculator::pop_until_LPAR() {
    while (!stack.empty() && stack.back()->getType() != 2) {
        postfix.emplace_back(stack.back());
        #ifdef DEBUG
        std::cout << "Postfix pushed: " << postfix.back()->toString() << std::endl;
        std::cout << "Stack popped: " << stack.back()->toString() << std::endl;
        #endif
        stack.pop_back();
    }
    #ifdef DEBUG
    std::cout << "Stack popped: " << stack.back()->toString() << std::endl;
    #endif
    stack.pop_back();
}

void Calculator::transform() {
    stack.clear(); // use as op stack;
    postfix.clear();
    for (auto it = tokens.begin(); it != tokens.end(); it++) {
        if ((*it)->getType() == 0) {
            // DataToken
            postfix.emplace_back((*it));
            #ifdef DEBUG
            std::cout << "Postfix pushed: " << postfix.back()->toString() << std::endl;
            #endif
        } else if ((*it)->getType() == 1) {
            // OpToken
            while (true) {
                if (stack.empty() || stack.back()->getType() == 2 || //LPAR
                std::dynamic_pointer_cast<OpToken>(stack.back())->getPriority()
                < std::dynamic_pointer_cast<OpToken>(*it)->getPriority())
                {
                    stack.emplace_back((*it));
                    #ifdef DEBUG
                    std::cout << "Stack pushed: " << stack.back()->toString() << std::endl;
                    #endif
                    break;
                } else {
                    postfix.emplace_back(stack.back());
                    #ifdef DEBUG
                    std::cout << "Postfix pushed: " << postfix.back()->toString() << std::endl;
                    std::cout << "Stack popped: " << stack.back()->toString() << std::endl;
                    #endif
                    stack.pop_back();
                }
            }
        } else if ((*it)->getType() == 2) {
            if (std::dynamic_pointer_cast<Parenthesis>(*it)->LorR() == 0) {
                stack.emplace_back((*it));
                #ifdef DEBUG
                std::cout << "Meeting: (" << std::endl;
                std::cout << "Stack pushed: " << stack.back()->toString() << std::endl;
                #endif
            } else {
                #ifdef DEBUG
                std::cout << "Meeting: )" << std::endl;
                #endif
                pop_until_LPAR();
            }
        }
    }
    while (!stack.empty()) {
        postfix.emplace_back(stack.back());
        #ifdef DEBUG
        std::cout << "Postfix pushed: " << postfix.back()->toString() << std::endl;
        std::cout << "Stack popped: " << stack.back()->toString() << std::endl;
        #endif
        stack.pop_back();
    }
    #ifdef DEBUG
    std::cout << "Got postfix: ";
    for (auto it = postfix.begin(); it != postfix.end(); it++) {
        std::cout << (*it)->toString() << ' ';
    }
    std::cout << std::endl;
    #endif
}

std::shared_ptr<DataToken> Calculator::calculate() {
    stack.clear();
    for (auto it = postfix.begin(); it != postfix.end(); it++) {
        #ifdef DEBUG
        std::cout << "Calculating pos:" << it - postfix.begin() << std::endl;
        #endif
        if ((*it)->getType() == 0) {
            // DataToken
            stack.emplace_back((*it));
        } else if ((*it)->getType() == 1) {
            // OpToken
            std::shared_ptr<DataToken> right = std::dynamic_pointer_cast<DataToken>(stack.back());
            stack.pop_back();
            std::shared_ptr<DataToken> left = std::dynamic_pointer_cast<DataToken>(stack.back());
            stack.pop_back();
            #ifdef DEBUG
            std::cout << "Calculating: " << left->toString() + ' ' + (*it)->toString() + ' ' + right->toString() << std::endl;
            #endif
            std::shared_ptr<DataToken> res = std::dynamic_pointer_cast<OpToken>(*it)->calc(left, right);
            if (res == nullptr) {
                throw InvalidCalculation("Invalid calculation of " + (*it)->toString() + " on " + left->toString() + " and " + right->toString());
            } else {
                stack.emplace_back(res);
            }
        }
    }
    #ifdef DEBUG
    std::cout << "Returning from calculate()" << std::endl;
    #endif
    return std::dynamic_pointer_cast<DataToken>(stack.back());
}

void Calculator::run(const std::string& input) {
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
    stack.clear();
    postfix.clear();
    tokens.clear();
}
