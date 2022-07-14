
#include "Operation.hpp"
#include "tokenize/LexicalAnalyzer.hpp"
#include "math.h"
#include "InvalidFormulaException.hpp"

Operation::Operation(char symbol) : symbol(symbol) {
    switch (symbol) {
        case '+':
        case '-':
            precedence = 1;
            break;
        case '*':
        case '/':
            precedence = 2;
            break;
        case '^':
            precedence = 3;
            break;
        default:
            throw InvalidFormulaException("Illegal char " + std::string(1, symbol));
    }
}

int Operation::getPrecedence() const {
    return precedence;
}

long double Operation::resolve(std::map<std::string, long double> vars, std::shared_ptr<Expression> op1,
                               std::shared_ptr<Expression> op2) const {
    switch (symbol) {
        case '+':
            return op1->resolve(vars) + op2->resolve(vars);
        case '-':
            return op1->resolve(vars) - op2->resolve(vars);
        case '*':
            return op1->resolve(vars) * op2->resolve(vars);
        case '/':
            return op1->resolve(vars) / op2->resolve(vars);
        case '^':
            return powl(op1->resolve(vars), op2->resolve(vars));
        default:
            throw InvalidFormulaException("Illegal symbol " + std::string(1, symbol));
    }
}

bool Operation::openForInput() const {
    return false;
}

std::string Operation::toString() const {
    return std::string(1, symbol);
}

bool Operation::match(char symbol) {
    switch (symbol) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
        default:
            return false;
    }
}