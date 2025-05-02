#include "Tokenizer.h"

#include <algorithm>
#include <iostream>

#include "Exception.h"

bool Tokenizer::isOperator(const std::string& s) const
{
    return op.end() > std::find(op.begin(), op.end(), s);
}

bool Tokenizer::isDigit(const std::string& s)const
{
    return digit.end() > std::find(digit.begin(), digit.end(), s);
}

std::string Tokenizer::getDigit(const std::string& s, int& pos)const {
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

std::string Tokenizer::getOperator(const std::string& s, int& pos)const {
    std::string ans = "";
    while (pos < s.size() && isOperator(s.substr(pos, 1))) {
        ans += s[pos++];
    }
    return ans;
}

void Tokenizer::skipSpace(const std::string& s, int& pos)const {
    while (pos < s.size() && (s[pos] == ' ' || s[pos] == '\t')) {
        pos++;
    }
}

void Tokenizer::tokenize(std::vector<BaseToken *> &tokens, std::string input)
{
    int pos = 0;
    skipSpace(input, pos);
    if (pos == input.size()) {
        throw NoExpression("No expression");
    }
    while (pos < input.size()) {
        if (pos == input.size()) {break;}

        std::string current = getDigit(input, pos);
        #ifdef DEBUG
        std::cout << "pos: " << pos << ", current: " << current << std::endl;
        #endif
        if (current == "") {
            throw LackingDigit("Expected digit, got: \"" + input.substr(pos, 1) + "\", at " + std::to_string(pos));
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
            throw InvalidDigit("Invalid number: \"" + current + "\", at " + std::to_string(pos));
            }
        }

        skipSpace(input, pos);
        if (pos == input.size()) {break;}

        current = getOperator(input, pos);
        #ifdef DEBUG
        std::cout << "pos: " << pos << ", current: " << current << std::endl;
        #endif
        if (current == "") {
            throw LackingOperator("Expected operator, got: \"" + input.substr(pos, 1) + "\", at " + std::to_string(pos));
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
            } else if (current == "^") {
                tokens.push_back(new POW());
            } else if (current == "%") {
                tokens.push_back(new MOD());
            } else if (current == "//") {
                tokens.push_back(new IDIV());
            } else {
                throw InvalidOperator("Invalid operator: \"" + current + "\", at " + std::to_string(pos));
            }
        }

        skipSpace(input, pos);
        if (pos == input.size()) {
            throw LackingDigit("Expected digit, got: \"\", at " + std::to_string(pos));
        }
    }
}


