#pragma once
#include <stdexcept>
#include <string>

class InvalidDigit : public std::runtime_error {
public:
    InvalidDigit(const std::string &message) : std::runtime_error(message) {}
    InvalidDigit(const char *message) : std::runtime_error(message) {}
};

class InvalidOperator : public std::runtime_error {
public:
    InvalidOperator(const std::string &message) : std::runtime_error(message) {}
    InvalidOperator(const char *message) : std::runtime_error(message) {}
};

class LackingDigit : public std::runtime_error {
public:
    LackingDigit(const std::string &message) : std::runtime_error(message) {}
    LackingDigit(const char *message) : std::runtime_error(message) {}
};

class LackingOperator : public std::runtime_error {
public:
    LackingOperator(const std::string &message) : std::runtime_error(message) {}
    LackingOperator(const char *message) : std::runtime_error(message) {}
};

class InvalidCalculation : public std::runtime_error {
public:
    InvalidCalculation(const std::string &message) : std::runtime_error(message) {}
    InvalidCalculation(const char *message) : std::runtime_error(message) {}
};

class NoExpression : public std::runtime_error {
public:
    NoExpression(const std::string &message) : std::runtime_error(message) {}
    NoExpression(const char *message) : std::runtime_error(message) {}
};

class LackingRPAR : public std::runtime_error {
public:
    LackingRPAR(const std::string& message): std::runtime_error(message) {}
    LackingRPAR(const char* message): std::runtime_error(message) {}
};

class ExtraRPAR : public std::runtime_error {
public:
    ExtraRPAR(const std::string& message): std::runtime_error(message) {}
    ExtraRPAR(const char* message): std::runtime_error(message) {}
};

class UndefinedVariable : public std::runtime_error {
public:
    UndefinedVariable(const std::string &message) : std::runtime_error(message) {}
    UndefinedVariable(const char *message) : std::runtime_error(message) {}
};

class UndefinedFunction : public std::runtime_error {
public:
    UndefinedFunction(const std::string &message) : std::runtime_error(message) {}
    UndefinedFunction(const char *message) : std::runtime_error(message) {}
};

class InvalidArguments : public std::runtime_error {
public:
    InvalidArguments(const std::string &message) : std::runtime_error(message) {}
    InvalidArguments(const char *message) : std::runtime_error(message) {}
};

class SyntaxError : public std::runtime_error {
public:
    SyntaxError(const std::string &message) : std::runtime_error(message) {}
    SyntaxError(const char *message) : std::runtime_error(message) {}
};