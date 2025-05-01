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

std::string Tokenizer::getDigit(std::string s, int& pos) {
    std::string ans = "";
    if (s[pos] == '-') {
        ans += s[pos++];
    }
    if (!isDigit(s.substr(pos, 1)))
        {return "";}
    while (pos < s.size() && isDigit(s.substr(pos, 1))) {
        ans += s[pos++];
    }
    return ans;
}

std::string Tokenizer::getOperator(std::string s, int& pos) {
    std::string ans = "";
    while (pos < s.size() && isOperator(s.substr(pos, 1))) {
        ans += s[pos++];
    }
    return ans;
}

void Tokenizer::skipSpace(std::string s, int& pos) {
    while (pos < s.size() && s[pos] == ' ') {
        pos++;
    }
}

void Tokenizer::tokenize(std::vector<BaseToken *> &tokens, std::string input)
{
    int pos = 0;
    while (pos < input.size()) {
        #ifdef DEBUG
        std::cout << "pos: " << pos << ", current: " << current << std::endl;
        #endif
        skipSpace(input, pos);

        std::string current = getDigit(input, pos);
        if (current == "") {
            throw std::runtime_error("Expected digit, got: \"" + input.substr(pos, 1) + "\", at " + std::to_string(pos));
        } else {
            // cast to double
            size_t index = 0;
            double val = std::stod(current, &index);
            if (index == current.size()) {
                if (val != int(val)) {
                    tokens.push_back(new DataToken(val));
                } else {
                    tokens.push_back(new DataToken(int(val)));
                }
            } else {
            // error
            throw std::runtime_error("Invalid number: \"" + current + "\", at " + std::to_string(pos));
            }
        }

        if (pos >= input.size()) {break;}
        skipSpace(input, pos);

        current = getOperator(input, pos);
        if (current == "") {
            throw std::runtime_error("Expected operator, got: \"" + input.substr(pos, 1) + "\", at " + std::to_string(pos));
        } else {
            // decide which op
            if (current == "+") {
                tokens.push_back(new ADD());
            } else if (current == "-") {
                tokens.push_back(new SUB());
            } else if (current == "*") {
                tokens.push_back(new MUL());
            } else if (current == "/") {
                tokens.push_back(new DIV());
            } else {
                throw std::runtime_error("Invalid operator: \"" + current + "\", at " + std::to_string(pos));
            }
        }
    }
}


