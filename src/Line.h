#pragma once
#include <string>

class Interpreter;

class Line{
protected:
    std::string expr;
    int LineNumber;
public:
    Line(const std::string& _expr, int _LineNumber):
        expr(_expr), 
        LineNumber(_LineNumber)
    {}
    virtual ~Line() {}
    virtual std::string execute(Interpreter* const) const = 0;
    virtual int getType() const { return 0;}
    // 0 for default
    #ifdef iDEBUG
    virtual void show() const = 0;
    #endif

    friend Interpreter;
};

class LET: public Line{
public:
    LET(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~LET() override {}
    std::string execute(Interpreter* const) const override;
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class PRINT: public Line{
public:
    PRINT(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~PRINT() override {}
    std::string execute(Interpreter* const) const override;
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class DEF: public Line{
    int end = 0;
public:
    DEF(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~DEF() override {}
    void setEnd(int _end) { end = _end; }
    std::string execute(Interpreter* const) const override;
    int getType() const override { return 1; }
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class END_DEF: public Line{
    int begin = 0;
public:
    END_DEF(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~END_DEF() override {}
    void setBegin(int _begin) { begin = _begin; }
    std::string execute(Interpreter* const) const override;
    int getType() const override { return 2; }
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class IF: public Line{
    int end = 0;
public:
    IF(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~IF() override {}
    void setEnd(int _end) { end = _end; }
    std::string execute(Interpreter* const) const override;
    int getType() const override { return 3; }
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class END_IF: public Line{
    int begin = 0;
public:
    END_IF(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~END_IF() override {}
    void setBegin(int _begin) { begin = _begin; }
    std::string execute(Interpreter* const) const override;
    int getType() const override { return 4; }
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class WHILE: public Line{
    int end = 0;
public:
    WHILE(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~WHILE() override {}
    void setEnd(int _end) { end = _end; }
    std::string execute(Interpreter* const) const override;
    int getType() const override { return 5; }
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class END_WHILE: public Line{
    int begin = 0;
public:
    END_WHILE(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~END_WHILE() override {}
    void setBegin(int _begin) { begin = _begin; }
    std::string execute(Interpreter* const) const override;
    int getType() const override { return 6; }
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class RET: public Line{
public:
    RET(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~RET() override {}
    std::string execute(Interpreter* const) const override;
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class EXPR: public Line{
public:
    EXPR(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~EXPR() override {}
    std::string execute(Interpreter* const) const override;
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};

class CMT: public Line{
public:
    CMT(const std::string& expr, int LineNumber) : Line(expr, LineNumber) {}
    ~CMT() override {}
    std::string execute(Interpreter* const) const override;
    #ifdef iDEBUG
    virtual void show() const override;
    #endif
};