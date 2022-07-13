#pragma once

#include <memory>
#include "LexicalAnalyzer.hpp"

class Token;

class Operation;

class ASTNode {
public:
    virtual bool openForInput() = 0;
    virtual std::string toString() = 0;
};

class Expression : public ASTNode {
public:
    virtual std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) = 0;

    virtual long double resolve() = 0;

    virtual std::shared_ptr<Expression> simplify() = 0;

    virtual void validate() {

    }
};

class BinaryOperationExpression : public Expression, public std::enable_shared_from_this<BinaryOperationExpression> {
private:
    std::shared_ptr<Expression> op1;
    std::shared_ptr<Expression> op2;
    std::shared_ptr<Operation> op;
public:
    BinaryOperationExpression(std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op);
    BinaryOperationExpression(std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op, std::shared_ptr<Expression> op2);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve();

    std::shared_ptr<Expression> simplify();

    void validate();

    bool openForInput();

    std::string toString();
};

class Number : public Expression, public std::enable_shared_from_this<Number> {
private:
    long double val;
public:
    Number(long double val);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve();

    std::shared_ptr<Expression> simplify();

    bool openForInput();

    std::string toString();
};

#define PARENTHESIS_OPEN '('
#define PARENTHESIS_CLOSED ')'

class Parenthesis : public Expression, public std::enable_shared_from_this<Parenthesis> {
private:
    std::shared_ptr<Expression> nestedExp;
    bool closed;
    char c;
public:
    Parenthesis(char c);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve();

    std::shared_ptr<Expression> simplify();

    bool openForInput();

    void validate();

    std::string toString();
};

class Operation : public ASTNode {
private:
    char symbol;
    int precedence;
public:
    Operation(char symbol);

    int getPrecedence() const;

    long double resolve(std::shared_ptr<Expression> op1, std::shared_ptr<Expression> op2);

    bool openForInput();

    std::string toString();
};

class ASTBuilder {
public:
    std::shared_ptr<Expression> tokensToExpression(std::vector<std::shared_ptr<Token>> tokens);


};
