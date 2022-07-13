
#include "ASTBuilder.hpp"

#include <math.h>

/* *************************************************************************************************** */

BinaryOperationExpression::BinaryOperationExpression(std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op)
        : op1(op1), op(op) {
}

BinaryOperationExpression::BinaryOperationExpression(std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op,
                                                     std::shared_ptr<Expression> op2)
        : op1(op1), op(op), op2(op2) {
}

std::shared_ptr<Expression> BinaryOperationExpression::add(std::shared_ptr<ASTNode> toAdd) {
    if (op2 && op2->openForInput()) {
        op2->add(toAdd);
        return shared_from_this();
    }
    if (auto toAddOp = std::dynamic_pointer_cast<Operation>(toAdd)) {
        if (op->getPrecedence() < toAddOp->getPrecedence()) {
            return std::make_shared<BinaryOperationExpression>(op1, op, std::make_shared<BinaryOperationExpression>(
                    op2, toAddOp));
        } else {
            return std::make_shared<BinaryOperationExpression>(shared_from_this(), toAddOp);
        }
    } else {
        op2 = std::static_pointer_cast<Expression>(toAdd);
        return shared_from_this();
    }
}

long double BinaryOperationExpression::resolve() {
    return op->resolve(op1, op2);
}

std::shared_ptr<Expression> BinaryOperationExpression::simplify() {
    return shared_from_this();
}

void BinaryOperationExpression::validate() {
    if (!op2) {
        throw std::error_code();
    }
    op1->validate();
    op2->validate();
}

bool BinaryOperationExpression::openForInput() {
    return !op2 || op2->openForInput();
}

std::string BinaryOperationExpression::toString() {
    return "(" + op1->toString() + op->toString() + op2->toString() + ")";
}

/* *************************************************************************************************** */

Number::Number(long double val) : val(val) {
}

std::shared_ptr<Expression> Number::add(std::shared_ptr<ASTNode> toAdd) {
    return std::make_shared<BinaryOperationExpression>(shared_from_this(), std::static_pointer_cast<Operation>(toAdd));
}

long double Number::resolve() {
    return val;
}

std::shared_ptr<Expression> Number::simplify() {
    return shared_from_this();
}

bool Number::openForInput() {
    return false;
}

std::string Number::toString() {
    return std::to_string(val);
}

/* *************************************************************************************************** */

Parenthesis::Parenthesis(char c) : c(c), closed(false) {
}

std::shared_ptr<Expression> Parenthesis::add(std::shared_ptr<ASTNode> toAdd) {
    if (closed) {
        auto toAddOp = std::dynamic_pointer_cast<Operation>(toAdd);
        if (!toAddOp) {
            // TODO: this must never happen. Error is actually LexicalAnalyzer.
            throw new InvalidFormulaException("Missing opening (");
        }
        return std::make_shared<BinaryOperationExpression>(shared_from_this(), toAddOp);
    }
    if (!nestedExp) {
        nestedExp = std::static_pointer_cast<Expression>(toAdd);
    } else {
        if (std::dynamic_pointer_cast<Parenthesis>(toAdd) && !nestedExp->openForInput()) {
            closed = true;
        } else {
            nestedExp = nestedExp->add(toAdd);
        }
    }
    return shared_from_this();
}

long double Parenthesis::resolve() {
    return nestedExp->resolve();
}

std::shared_ptr<Expression> Parenthesis::simplify() {
    return nestedExp->simplify();
}

bool Parenthesis::openForInput() {
    return !closed;
}

void Parenthesis::validate() {
    if (c == ')') {
        throw new InvalidFormulaException("Missing opening (");
    } else if (!closed) {
        throw new InvalidFormulaException("Missing closing )");
    }
    nestedExp->validate();
}

std::string Parenthesis::toString() {
    return "(" + nestedExp->toString() + ")";
}

/* *************************************************************************************************** */

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
    }
}

int Operation::getPrecedence() const {
    return precedence;
}

long double Operation::resolve(std::shared_ptr<Expression> op1, std::shared_ptr<Expression> op2) {
    switch (symbol) {
        case '+':
            return op1->resolve() + op2->resolve();
        case '-':
            return op1->resolve() - op2->resolve();
        case '*':
            return op1->resolve() * op2->resolve();
        case '/':
            return op1->resolve() / op2->resolve();
        case '^':
            return powl(op1->resolve(), op2->resolve());
    }
    return 0;
}

bool Operation::openForInput() {
    return false;
}

std::string Operation::toString() {
    return std::string(1, symbol);
}

/* *************************************************************************************************** */

std::shared_ptr<Expression> ASTBuilder::tokensToExpression(std::vector<std::shared_ptr<Token>> tokens) {
    std::shared_ptr<Expression> resultExp;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        auto token = *it;
        std::shared_ptr<ASTNode> astNode = token->toASTNode();
        if (!resultExp) {
            resultExp = std::static_pointer_cast<Expression>(astNode);
        } else {
            resultExp = resultExp->add(astNode);
        }
    }
    resultExp->validate();
    return resultExp->simplify();
}

