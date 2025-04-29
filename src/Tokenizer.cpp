#include "Tokenizer.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

bool Tokenizer::isOperator(std::string s)
{
    return op.end() > std::find(op.begin(), op.end(), s);
}

bool Tokenizer::isDigit(std::string s)
{
    return digit.end() > std::find(digit.begin(), digit.end(), s);
}

void Tokenizer::tokenize(std::vector<BaseToken *> &tokens, std::string input)
{
    std::string current = "";
    int pos = 0;
    while (pos < input.size()) {
        #ifdef DEBUG
        std::cout << "pos: " << pos << ", current: " << current << std::endl;
        #endif
        if (input.substr(pos, 1) == " ") {
            pos++;
            continue;
        } else if (isDigit(input.substr(pos, 1))) {
            do {
                current += input[pos++];
            } while (pos < input.size() && isDigit(input.substr(pos, 1)));
            
            #ifdef DEBUG
            std::cout << "Tokeneized digit: " << current << std::endl;
            #endif

            // cast to double
            size_t index = 0;
            double val = std::stod(current, &index);
            if (index == current.size()) {
                tokens.push_back(new DataToken(val));
                current = "";
                continue;
            } 

            // cast to int
            index = 0;
            int val2 = std::stoi(current, &index);
            if (index == current.size()) {
                tokens.push_back(new DataToken(val2));
                current = "";
                continue;
            }

            // error
            throw std::runtime_error("Invalid number: " + current + ", at " + std::to_string(pos));
        } else if (isOperator(input.substr(pos, 1))) {
            do {
                current += input[pos++];
            } while (pos < input.size() && isOperator(input.substr(pos, 1)));

            // decide which op
            if (current == "+") {
                tokens.push_back(new ADD());
            } 
            // else if (current == "-") {
            
            #ifdef DEBUG
            std::cout << "Tokeneized op: " << current << std::endl;
            #endif
            current = "";
        }
        else {
            throw std::runtime_error("Invalid character: " + input.substr(pos, 1) + ", at " + std::to_string(pos));
        }
    }
}


