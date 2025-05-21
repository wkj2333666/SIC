#pragma once
#include <stdexcept>
#include <string>

class CalcError : public std::runtime_error {
public:
    CalcError(const std::string &message) : std::runtime_error(message) {}
    CalcError(const char *message) : std::runtime_error(message) {}
};

class SyntaxError : public std::runtime_error {
public:
    SyntaxError(const std::string &message) : std::runtime_error(message) {}
    SyntaxError(const char *message) : std::runtime_error(message) {}
};

class InvalidDigit : public CalcError {
public:
    InvalidDigit(const std::string &message) : CalcError(message) {}
    InvalidDigit(const char *message) : CalcError(message) {}
};

class InvalidOperator : public CalcError {
public:
    InvalidOperator(const std::string &message) : CalcError(message) {}
    InvalidOperator(const char *message) : CalcError(message) {}
};

class LackingDigit : public CalcError {
public:
    LackingDigit(const std::string &message) : CalcError(message) {}
    LackingDigit(const char *message) : CalcError(message) {}
};

class LackingOperator : public CalcError {
public:
    LackingOperator(const std::string &message) : CalcError(message) {}
    LackingOperator(const char *message) : CalcError(message) {}
};

class InvalidCalculation : public CalcError {
public:
    InvalidCalculation(const std::string &message) : CalcError(message) {}
    InvalidCalculation(const char *message) : CalcError(message) {}
};

// class NoExpression : public CalcError {
// public:
//     NoExpression(const std::string &message) : CalcError(message) {}
//     NoExpression(const char *message) : CalcError(message) {}
// };

class LackingRPAR : public CalcError {
public:
    LackingRPAR(const std::string& message): CalcError(message) {}
    LackingRPAR(const char* message): CalcError(message) {}
};

class ExtraRPAR : public CalcError {
public:
    ExtraRPAR(const std::string& message): CalcError(message) {}
    ExtraRPAR(const char* message): CalcError(message) {}
};

class UndefinedVariable : public SyntaxError {
public:
    UndefinedVariable(const std::string &message) : SyntaxError(message) {}
    UndefinedVariable(const char *message) : SyntaxError(message) {}
};

class UndefinedFunction : public SyntaxError {
public:
    UndefinedFunction(const std::string &message) : SyntaxError(message) {}
    UndefinedFunction(const char *message) : SyntaxError(message) {}
};

class InvalidArguments : public SyntaxError {
public:
    InvalidArguments(const std::string &message) : SyntaxError(message) {}
    InvalidArguments(const char *message) : SyntaxError(message) {}
};
