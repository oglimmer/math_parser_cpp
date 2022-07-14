
#pragma once

#include "ASTNode.hpp"
#include "Expression.hpp"


class Operation : public ASTNode {
private:
    char symbol;
    int precedence;
public:
    Operation(char symbol);

    int getPrecedence() const;

    long double resolve(std::map<std::string, long double> vars, std::shared_ptr<Expression> op1,
                        std::shared_ptr<Expression> op2) const;

    bool openForInput() const;

    std::string toString() const;

    static bool match(char symbol);
};