#include <sstream>
#include <iostream>

#include "Interpreter.h"
#include "Exception.h"

std::string Interpreter::CALL(const std::string& function_name, const std::string& args) {
    stack_for_call.push_back(CurrentLine);
    CurrentLine = functions[function_name];

    // get function declaration
    std::string function_declaration = codes[CurrentLine]->expr;

    // split arguments
    std::vector<std::string> split_args;
    std::string arg_buffer;
    std::stringstream ss(args);
    while (std::getline(ss, arg_buffer, ',')) {
        split_args.push_back(arg_buffer);
        arg_buffer.clear();
    }
    #ifdef iDEBUG
    std::cout << "function_name = " << function_name << std::endl;
    std::cout << "function_declaration = " << function_declaration << std::endl;
    std::cout << "args = " << args << std::endl;
    for (auto& arg : split_args) {
        std::cout << "arg = " << arg << std::endl;
    }
    #endif
    
    // get function params
    int num_of_args = split_args.size();
    std::sregex_iterator it(function_declaration.begin(), function_declaration.end(), regex_for_param_list);
    std::sregex_iterator end;

    int num_of_params = 0;
    for (; it != end; ++it) {
        num_of_params++;
        if (num_of_params > num_of_args) {throw InvalidArguments("At line " + std::to_string(CurrentLine + 1) + ": Invalid number of arguments for function " + function_name);}
        try {variables[(*it)[1].str()] = calculator->run(split_args[num_of_params - 1]);}
        catch (const CalcError& e) {
            throw SyntaxError("At line " + std::to_string(CurrentLine + 1) + ": " + e.what());
        }
    }
    if (num_of_params < num_of_args) {throw InvalidArguments("At line " + std::to_string(CurrentLine + 1) + ":Invalid number of arguments for function " + function_name);}
    #ifdef iDEBUG
    std::cout << "num_of_params = " << num_of_params << std::endl;
    #endif

    // execute function body
    CurrentLine++; // enter function body
    #ifdef iDEBUG
    std::cout << "CurrentLine: " << CurrentLine + 1<< std::endl;
    #endif
    std::string return_value;
    while ((return_value = codes[CurrentLine]->execute(this)) == ""){}

    // remove temporary variables
    for (; it != end; ++it) {
        variables.erase((*it)[1].str());
    }
    #ifdef iDEBUG
    std::cout << "return_value = " << return_value << std::endl;
    #endif

    return return_value;
}

std::string Interpreter::evaluate(const std::string& expression) {
    for (int i=0; i<expression.size(); i++) {
        if (!std::isspace(expression[i])) {
            try {return calculator->run(substitute_functions(substitute_variables(expression)));}
            catch (const CalcError& e) {
                throw SyntaxError("At line " + std::to_string(CurrentLine + 1) + ": " + e.what());
            }
        }
    }
    return " "; // differ from ""
}

std::string Interpreter::substitute_variables(const std::string& expression) {
    std::sregex_iterator it(expression.begin(), expression.end(), regex_for_variable);
    std::sregex_iterator end;
    size_t pos = 0;
    std::string result;

    for (; it != end; ++it) {
        std::smatch match = *it;
        result += match.prefix().str();
        std::string var_name = match[0].str();
        if (variables.find(var_name) != variables.end()) {
            result += variables[var_name];
        } else {
            throw UndefinedVariable("At line " + std::to_string(CurrentLine + 1) + ": Undefined variable: " + var_name);
        }
        pos = match.position() + match.length();
    }
    result += expression.substr(pos);
    return result;
}

std::string Interpreter::substitute_functions(const std::string& expression) {
    std::sregex_iterator it(expression.begin(), expression.end(), regex_for_function);
    std::sregex_iterator end;
    size_t pos = 0;
    std::string result;

    for (; it != end; ++it) {
        std::smatch match = *it;
        result += match.prefix().str();
        std::string function_name = match[1].str();
        std::string args = match[2].str();
        #ifdef iDEBUG
        std::cout << "function_name = " << function_name << std::endl;
        std::cout << "args = " << args << std::endl;
        #endif
        if (functions.find(function_name) != functions.end()) {
            args = substitute_functions(args);
            result += CALL(function_name, args);
            #ifdef iDEBUG
            std::cout << "Current substituted result: " << result << std::endl;
            #endif
        } else {
            throw UndefinedFunction("At line " + std::to_string(CurrentLine + 1) + ": Undefined function: " + function_name);
        }
        pos = match.position() + match.length();
    }
    result += expression.substr(pos);
    #ifdef iDEBUG
    std::cout << "Substituted expr: " << result << std::endl;
    #endif
    return result;
}

void Interpreter::parse_if() {
    std::vector<Line*> if_stack;
    for (auto line : codes) {
        if (line->getType() == 3) { // IF
            if_stack.push_back(line);
        } else if (line->getType() == 4) { // END_IF
            if (if_stack.empty())
                throw SyntaxError("At line " + std::to_string(line->LineNumber + 1) + ": No matching if for endif.");
            dynamic_cast<IF*>(if_stack.back())->setEnd(line->LineNumber);
            dynamic_cast<END_IF*>(line)->setBegin(if_stack.back()->LineNumber);
            if_stack.pop_back();
        }
    }
    if (!if_stack.empty())
        throw SyntaxError("At line " + std::to_string(if_stack.back()->LineNumber + 1) + ": No matching endif for if.");
}

void Interpreter::parse_def() {
    std::vector<Line*> def_stack;
    for (auto line : codes) {
        if (line->getType() == 1) { // DEF
            def_stack.push_back(line);
        } else if (line->getType() == 2) { // END_DEF
            if (def_stack.empty())
                throw SyntaxError("At line " + std::to_string(line->LineNumber + 1) + ": No matching def for enddef.");
            dynamic_cast<DEF*>(def_stack.back())->setEnd(line->LineNumber);
            dynamic_cast<END_DEF*>(line)->setBegin(def_stack.back()->LineNumber);
            def_stack.pop_back();
        }
    }
    if (!def_stack.empty())
        throw SyntaxError("At line " + std::to_string(def_stack.back()->LineNumber + 1) + ": No matching enddef for def.");
}

void Interpreter::parse_while() {
    std::vector<Line*> while_stack;
    for (auto line : codes) {
        if (line->getType() == 5) { // WHILE
            while_stack.push_back(line);
        } else if (line->getType() == 6) { // END_WHILE
            if (while_stack.empty())
                throw SyntaxError("At line " + std::to_string(line->LineNumber + 1) + ": No matching while for endwhile.");
            dynamic_cast<WHILE*>(while_stack.back())->setEnd(line->LineNumber);
            dynamic_cast<END_WHILE*>(line)->setBegin(while_stack.back()->LineNumber);
            while_stack.pop_back();
        }
    }
    if (!while_stack.empty())
        throw SyntaxError("At line " + std::to_string(while_stack.back()->LineNumber + 1) + ": No matching endwhile for while.");
}

void Interpreter::parse(std::fstream& code_file) {
    std::string buffer;
    int LineNumber = 0;
    while (std::getline(code_file, buffer)) {
        #ifdef iDEBUG
        std::cout << "Parsing line " << LineNumber << ": " << buffer << std::endl;
        #endif
        std::stringstream ss(buffer);
        std::string command;
        std::string expr;
        ss >> command;
        std::getline(ss, expr);
        #ifdef iDEBUG
        std::cout << "Command: " << command << std::endl;
        std::cout << "Expression: " << expr << std::endl;
        #endif

        if (command == "let") codes.push_back(new LET(expr, LineNumber));
        else if (command == "print") codes.push_back(new PRINT(expr, LineNumber));
        else if (command == "def") codes.push_back(new DEF(expr, LineNumber));
        else if (command == "enddef") codes.push_back(new END_DEF(expr, LineNumber));
        else if (command == "if") codes.push_back(new IF(expr, LineNumber));
        else if (command == "endif") codes.push_back(new END_IF(expr, LineNumber));
        else if (command == "while") codes.push_back(new WHILE(expr, LineNumber));
        else if (command == "endwhile") codes.push_back(new END_WHILE(expr, LineNumber));
        else if (command == "return") codes.push_back(new RET(expr, LineNumber));
        else if (command == "#") codes.push_back(new CMT(expr, LineNumber));
        else codes.push_back(new EXPR(buffer, LineNumber));

        LineNumber++;
    }
    parse_if();
    parse_def();
    parse_while();
}

void Interpreter::interpret(std::fstream& code_file) {
    #ifdef iDEBUG
    std::cout << "Starting interpreting..." << std::endl;
    std::cout << "Parsing..." << std::endl;
    #endif
    parse(code_file);
    #ifdef iDEBUG
    std::cout << "Parsing done. Total lines: " << codes.size() << std::endl;
    std::cout << "Result:" << std::endl;
    for (auto line : codes) {
        line->show();
    }
    std::cout << "CurrentLine: " << CurrentLine + 1 << std::endl;
    #endif
    while (CurrentLine < codes.size()) { // note that CurrentLine starts from 1.
        #ifdef iDEBUG
        std::cout << "Executing line " << CurrentLine + 1<< std::endl;
        #endif
        codes[CurrentLine]->execute(this);
    }
}
