#pragma once
#include <string>
#include <variant>

class BaseToken {
public:
    BaseToken() = default;
    virtual ~BaseToken() = default;
    virtual int getType() const= 0;
    // 0 for data, 1 for op;
};

class DataToken : public BaseToken {
    std::variant<int, double, std::string> data;
public:
    DataToken(): data(0){}
    DataToken(int value): data(value) {}
    DataToken(double value): data(value) {}
    DataToken(std::string value): data(value) {}
    ~DataToken() override = default;
    int getType()const override {return 0;}
    const std::variant<int, double>& getData() const {return data;}
    // auto getData() const;
};

class OpToken : public BaseToken {
    std::string name;
public:
    OpToken(std::string _name): name(_name) {}
    ~OpToken() override = default;
    int getType() const override {return 1;}

    virtual DataToken* calc(DataToken*, DataToken*) const= 0;
};

class ADD : public OpToken{
    int priority;
public:
    ADD(): OpToken("+"), priority(0) {}
    ~ADD() override = default;
    DataToken* calc(DataToken* , DataToken*) const override;
};

