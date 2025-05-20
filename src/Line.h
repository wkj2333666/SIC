#pragma once
#include <string>

class Interpreter;

class Line{
protected:
    std::string expr;
    static int CurrentLine;
public:
    Line(std::string expr, int LineNumber) {}
    virtual ~Line() {}
    virtual std::string execute(Interpreter*) = 0;

    friend Interpreter;
};

class LET: public Line{
public:
    LET(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~LET() override {}
    std::string execute(Interpreter*) override;
};

class PRINT: public Line{
public:
    PRINT(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~PRINT() override {}
    std::string execute(Interpreter*) override;
};

class DEF: public Line{
    int end = 0;
public:
    DEF(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~DEF() override {}
    void setEnd(int _end) { end = _end; }
    std::string execute(Interpreter*) override;
};

class END_DEF: public Line{
    int begin = 0;
public:
    END_DEF(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~END_DEF() override {}
    void setBegin(int _begin) { begin = _begin; }
    std::string execute(Interpreter*) override;
};

class IF: public Line{
    int end = 0;
public:
    IF(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~IF() override {}
    void setEnd(int _end) { end = _end; }
    std::string execute(Interpreter*) override;
};

class END_IF: public Line{
    int begin = 0;
public:
    END_IF(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~END_IF() override {}
    void setBegin(int _begin) { begin = _begin; }
    std::string execute(Interpreter*) override;
};

class WHILE: public Line{
    int end = 0;
public:
    WHILE(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~WHILE() override {}
    void setEnd(int _end) { end = _end; }
    std::string execute(Interpreter*) override;
};

class END_WHILE: public Line{
    int begin = 0;
public:
    END_WHILE(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~END_WHILE() override {}
    void setBegin(int _begin) { begin = _begin; }
    std::string execute(Interpreter*) override;
};

class RET: public Line{
public:
    RET(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~RET() override {}
    std::string execute(Interpreter*) override;
};

class EXPR: public Line{
public:
    EXPR(std::string expr, int LineNumber) : Line(expr, LineNumber) {}
    ~EXPR() override {}
    std::string execute(Interpreter*) override;
};