#include "Token.h"
#include <iostream>
// auto DataToken::getData() const{
//     if (data.type() == typeid(int)) {
//         return std::any_cast<int>(data);
//     }
//     else if (data.type() == typeid(double)) {
//         return std::any_cast<double>(data);
//     }
// }

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


DataToken* ADD::calc(DataToken* left, DataToken* right) const{
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

DataToken* SUB::calc(DataToken* left, DataToken* right) const{
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

DataToken* MUL::calc(DataToken* left, DataToken* right) const{
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

DataToken* DIV::calc(DataToken* left, DataToken* right) const{
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