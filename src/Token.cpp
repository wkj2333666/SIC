#include "Token.h"

#include <iostream>
#include <cmath>

std::string DataToken::toString() const{
    if (data.index() == 0) {
        return std::to_string(std::get<int>(data));
    } else if (data.index() == 1) {
        return std::to_string(std::get<double>(data));
    } else if (data.index() == 2) {
        return std::get<std::string>(data);
    }
    return ""; // never will
}

std::ostream& operator<<(std::ostream& os, const DataToken& token) {
    #ifdef DEBUG
    std::cout << "Printing" << std::endl;
    #endif
    switch (token.getData().index()) {
        case 0:
            os << std::get<int>(token.getData());
            break;
        case 1:
            os << std::get<double>(token.getData());
            break;
        case 2:
            os << std::get<std::string>(token.getData());
            break;
    }
    return os;
}


DataToken* ADD::calc(const DataToken* const left, const DataToken* const right) const{
    if (left->getData().index() == 0 && right->getData().index() == 0) {
        return new DataToken(std::get<int>(left->getData()) + std::get<int>(right->getData()));
    } else if (left->getData().index() == 0 && right->getData().index() == 1) {
        return new DataToken(std::get<int>(left->getData()) + std::get<double>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 0) {
        return new DataToken(std::get<double>(left->getData()) + std::get<int>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 1) {
        return new DataToken(std::get<double>(left->getData()) + std::get<double>(right->getData()));
    } else if (left->getData().index() == 2 && right->getData().index() == 2) {
        return new DataToken(std::get<std::string>(left->getData()) + std::get<std::string>(right->getData()));
    }
    return nullptr; // invalid ADD operation!
}

int OpToken::getPriority() const{
    return priority;
}

DataToken* SUB::calc(const DataToken* const left, const DataToken* const right) const{
    if (left->getData().index() == 0 && right->getData().index() == 0) {
        return new DataToken(std::get<int>(left->getData()) - std::get<int>(right->getData()));
    } else if (left->getData().index() == 0 && right->getData().index() == 1) {
        return new DataToken(std::get<int>(left->getData()) - std::get<double>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 0) {
        return new DataToken(std::get<double>(left->getData()) - std::get<int>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 1) {
        return new DataToken(std::get<double>(left->getData()) - std::get<double>(right->getData()));
    }
    return nullptr; // invalid SUB operation!
}

DataToken* MUL::calc(const DataToken* const left, const DataToken* const right) const{
    if (left->getData().index() == 0 && right->getData().index() == 0) {
        return new DataToken(std::get<int>(left->getData()) * std::get<int>(right->getData()));
    } else if (left->getData().index() == 0 && right->getData().index() == 1) {
        return new DataToken(std::get<int>(left->getData()) * std::get<double>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 0) {
        return new DataToken(std::get<double>(left->getData()) * std::get<int>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 1) {
        return new DataToken(std::get<double>(left->getData()) * std::get<double>(right->getData()));
    }
    return nullptr; // invalid MUL operation!
}

DataToken* DIV::calc(const DataToken* const left, const DataToken* const right) const{
    if (left->getData().index() == 0 && right->getData().index() == 0) {
        return new DataToken(std::get<int>(left->getData()) / static_cast<double>(std::get<int>(right->getData())));
    } else if (left->getData().index() == 0 && right->getData().index() == 1) {
        return new DataToken(std::get<int>(left->getData()) / std::get<double>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 0) {
        return new DataToken(std::get<double>(left->getData()) / std::get<int>(right->getData()));
    } else if (left->getData().index() == 1 && right->getData().index() == 1) {
        return new DataToken(std::get<double>(left->getData()) / std::get<double>(right->getData()));
    }
    return nullptr; // invalid DIV operation!
}

DataToken* POW::calc(const DataToken* const left, const DataToken* const right) const{
    if (left->getData().index() == 0 && right->getData().index() == 0) {
        return new DataToken(std::pow(std::get<int>(left->getData()), std::get<int>(right->getData())));
    } else if (left->getData().index() == 0 && right->getData().index()) {
        return new DataToken(std::pow(std::get<int>(left->getData()), std::get<double>(right->getData())));
    } else if (left->getData().index() == 1 && right->getData().index() == 0) {
        return new DataToken(std::pow(std::get<double>(left->getData()), std::get<int>(right->getData())));
    } else if (left->getData().index() == 1 && right->getData().index() == 1) {
        return new DataToken(std::pow(std::get<double>(left->getData()), std::get<double>(right->getData())));
    }
    return nullptr; // invalid POW operation!
}

DataToken* MOD::calc(const DataToken* const left, const DataToken* const right) const{
    if (left->getData().index() == 0 && right->getData().index() == 0) {
        return new DataToken(std::get<int>(left->getData()) % std::get<int>(right->getData()));
    }
    return nullptr; // invalid MOD operation!
}

DataToken* IDIV::calc(const DataToken* const left, const DataToken* const right) const{
    if (left->getData().index() == 0 && right->getData().index() == 0) {
        return new DataToken(std::get<int>(left->getData()) / std::get<int>(right->getData()));
    }
    return nullptr; // invalid IDIV operation!
}