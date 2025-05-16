#include "Tokenizer.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <functional>

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

void Tokenizer::skipSpace(std::vector<std::shared_ptr<BaseToken>>& tokens, const std::string& s, int& pos){
    while (pos < s.size() && (s[pos] == ' ' || s[pos] == '\t') || s[pos] == '(' || s[pos] == ')') {
        if (s[pos] == '(') {
            tokens.emplace_back(std::make_shared<LPAR>());
            #ifdef DEBUG
            std::cout << "pos: " << pos+1 << ", current: (" << std::endl;
            #endif
            LoverR++;
        } else if (s[pos] == ')') {
            tokens.emplace_back(std::make_shared<RPAR>());
            #ifdef DEBUG
            std::cout << "pos: " << pos+1 << ", current: )" << std::endl;
            #endif
            LoverR--;
        }
        pos++;
    }
}

void Tokenizer::tokenize(std::vector<std::shared_ptr<BaseToken>> &tokens,const std::string& input)
{
    int pos = 0;
    LoverR = 0;
    skipSpace(tokens, input, pos);
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
                    tokens.emplace_back(std::make_shared<DataToken>(val));
                } else {
                    tokens.emplace_back(std::make_shared<DataToken>(int(val)));
                }
            } else {
            // error
            throw InvalidDigit("Invalid number: \"" + current + "\", at " + std::to_string(pos));
            }
        }

        skipSpace(tokens, input, pos);
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
                tokens.emplace_back(std::make_shared<ADD>());
            } else if (current == "-") {
                tokens.emplace_back(std::make_shared<SUB>());
            } else if (current == "*") {
                tokens.emplace_back(std::make_shared<MUL>());
            } else if (current == "/") {
                tokens.emplace_back(std::make_shared<DIV>());
            } else if (current == "^") {
                tokens.emplace_back(std::make_shared<POW>());
            } else if (current == "%") {
                tokens.emplace_back(std::make_shared<MOD>());
            } else if (current == "//") {
                tokens.emplace_back(std::make_shared<IDIV>());
            } else {
                throw InvalidOperator("Invalid operator: \"" + current + "\", at " + std::to_string(pos));
            }
        }

        skipSpace(tokens, input, pos);
        if (pos == input.size()) {
            throw LackingDigit("Expected digit, got: \"\", at " + std::to_string(pos));
        }
    }
    if (LoverR > 0) {
        throw LackingRPAR("Lacking right parenthesis");
    } else if (LoverR < 0) {
        throw ExtraRPAR("Extra right parenthesis");
    }
}
