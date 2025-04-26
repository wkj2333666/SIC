#include "Token.h"

auto DataToken::getData() const{
    if (data.type() == typeid(int)) {
        return std::any_cast<int>(data);
    }
    else if (data.type() == typeid(double)) {
        return std::any_cast<double>(data);
    }
}

DataToken* ADD::calc() const override {
    
}