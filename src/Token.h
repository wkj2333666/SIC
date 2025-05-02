#pragma once
#include <string>
#include <variant>

class BaseToken {
public:
    BaseToken() = default;
    virtual ~BaseToken() = default;
    virtual int getType() const= 0;
    virtual std::string toString() const = 0;
    // 0 for data, 1 for op;
};

class DataToken : public BaseToken {
    std::variant<int, double, std::string> data;
public:
    DataToken(): data(0){}
    DataToken(int value): data(value) {}
    DataToken(double value): data(value) {}
    DataToken(const std::string& value): data(value) {}
    ~DataToken() override = default;
    int getType()const override {return 0;}
    const std::variant<int, double, std::string>& getData() const {return data;}
    friend std::ostream& operator<<(std::ostream& os, const DataToken& token);
    std::string toString() const override;
};

class OpToken : public BaseToken {
    std::string name;
    int priority;
public:
    OpToken(const std::string& _name, int _priority): name(_name), priority(_priority) {}
    ~OpToken() override = default;
    int getType() const override {return 1;}
    int getPriority() const;
    std::string toString() const override{return name;}
    virtual DataToken* calc(const DataToken* const, const DataToken* const) const= 0;
};

class ADD : public OpToken{
public:
    ADD(): OpToken("+", 0) {}
    ~ADD() override = default;
    DataToken* calc(const DataToken* const , const DataToken* const) const override;
};

class SUB : public OpToken{
public:
    SUB(): OpToken("-", 0) {}
    ~SUB() override = default;
    DataToken* calc(const DataToken* const , const DataToken* const) const override;
};

class MUL : public OpToken{
public:
    MUL(): OpToken("*", 1) {}
    ~MUL() override = default;
    DataToken* calc(const DataToken* const , const DataToken* const) const override;
};

class DIV : public OpToken{
public:
    DIV(): OpToken("/", 1) {}
    ~DIV() override = default;
    DataToken* calc(const DataToken* const , const DataToken* const) const override;
};

class POW : public OpToken{
public:
    POW(): OpToken("^", 2) {}
    ~POW() override = default;
    DataToken* calc(const DataToken* const , const DataToken* const) const override;
};

class MOD : public OpToken{
public:
    MOD(): OpToken("%", 1) {}
    ~MOD() override = default;
    DataToken* calc(const DataToken* const , const DataToken* const) const override;
};

class IDIV : public OpToken{
public:
    IDIV(): OpToken("//", 1) {}
    ~IDIV() override = default;
    DataToken* calc(const DataToken* const , const DataToken* const) const override;
};