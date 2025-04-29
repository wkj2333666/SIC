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
    const std::variant<int, double, std::string>& getData() const {return data;}
    friend std::ostream& operator<<(std::ostream& os, const DataToken& token);
    // auto getData() const;
};

class OpToken : public BaseToken {
    std::string name;
    int priority;
public:
    OpToken(std::string _name, int _priority): name(_name), priority(_priority) {}
    ~OpToken() override = default;
    int getType() const override {return 1;}
    int getPriority() const;
    virtual DataToken* calc(DataToken*, DataToken*) const= 0;
};

class ADD : public OpToken{
public:
    ADD(): OpToken("+", 0) {}
    ~ADD() override = default;
    DataToken* calc(DataToken* , DataToken*) const override;
};

