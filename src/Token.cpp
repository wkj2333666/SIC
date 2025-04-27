#include "Token.h"

// auto DataToken::getData() const{
//     if (data.type() == typeid(int)) {
//         return std::any_cast<int>(data);
//     }
//     else if (data.type() == typeid(double)) {
//         return std::any_cast<double>(data);
//     }
// }

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