#pragma once
#include <string>
#include <variant>
#include <memory>

#include "None.h"

#define TYPE std::variant<int, double, std::string, bool, None>

class BaseToken {
public:
    BaseToken() = default;
    virtual ~BaseToken() = default;
    virtual int getType() const= 0;
    virtual std::string toString() const = 0;
    // 0 for data, 1 for op;
};

class DataToken : public BaseToken {
    TYPE data;
public:
    // DataToken(): data(0){}
    DataToken(int value): data(value) {}
    DataToken(double value): data(value) {}
    DataToken(const std::string& value): data(value) {}
    DataToken(bool value): data(value) {}
    DataToken(): data(None()) {}
    ~DataToken() override = default;
    int getType()const override {return 0;}
    const TYPE& getData() const {return data;}
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
    virtual std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken>, const std::shared_ptr<const DataToken>) const= 0;
};

class ADD : public OpToken{
public:
    ADD(): OpToken("+", 1) {}
    ~ADD() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class SUB : public OpToken{
public:
    SUB(): OpToken("-", 1) {}
    ~SUB() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class MUL : public OpToken{
public:
    MUL(): OpToken("*", 2) {}
    ~MUL() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class DIV : public OpToken{
public:
    DIV(): OpToken("/", 2) {}
    ~DIV() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class POW : public OpToken{
public:
    POW(): OpToken("^", 3) {}
    ~POW() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class MOD : public OpToken{
public:
    MOD(): OpToken("%", 2) {}
    ~MOD() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class IDIV : public OpToken{
public:
    IDIV(): OpToken("//", 2) {}
    ~IDIV() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class EQ : public OpToken{
public:
    EQ(): OpToken("==", 0) {}
    ~EQ() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class NE : public OpToken{
public:
    NE(): OpToken("!=", 0) {}
    ~NE() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class GT : public OpToken{
public:
    GT(): OpToken(">", 0) {}
    ~GT() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class GE : public OpToken{
public:
    GE(): OpToken(">=", 0) {}
    ~GE() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class LT : public OpToken{
public:
    LT(): OpToken("<", 0) {}
    ~LT() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class LE : public OpToken{
public:
    LE(): OpToken("<=", 0) {}
    ~LE() override = default;
    std::shared_ptr<DataToken> calc(const std::shared_ptr<const DataToken> , const std::shared_ptr<const DataToken>) const override;
};

class Parenthesis : public BaseToken {
public:
    Parenthesis() = default;
    ~Parenthesis() override = default;
    int getType() const override {return 2;}
    // 0 for left, 1 for right
    virtual int LorR() const = 0;
    std::string toString() const = 0;
};

class LPAR : public Parenthesis {
public:
    LPAR(): Parenthesis() {}
    ~LPAR() override = default;
    int LorR() const override {return 0;}
    std::string toString() const override {return "(";}
};

class RPAR : public Parenthesis {
public:
    RPAR(): Parenthesis() {}
    ~RPAR() override = default;
    int LorR() const override {return 1;}
    std::string toString() const override {return ")";}
};