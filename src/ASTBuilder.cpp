
#include "ASTBuilder.hpp"

#include <math.h>
#include <algorithm>

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

long double BinaryOperationExpression::resolve(std::map<std::string, long double> vars) {
    return op->resolve(vars, op1, op2);
}

std::shared_ptr<Expression> BinaryOperationExpression::simplify() {
    return shared_from_this();
}

void BinaryOperationExpression::validate() {
    if (!op2) {
        throw InvalidFormulaException("op2 must not be null");
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

long double Number::resolve(std::map<std::string, long double> vars) {
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

Constant::Constant(const std::string &constantName) : constantName(constantName) {
    std::transform(this->constantName.begin(), this->constantName.end(), this->constantName.begin(), ::toupper);
}

std::shared_ptr<Expression> Constant::add(std::shared_ptr<ASTNode> toAdd) {
    return std::make_shared<BinaryOperationExpression>(shared_from_this(), std::static_pointer_cast<Operation>(toAdd));
}

long double Constant::resolve(std::map<std::string, long double> vars) {
    if (constantName == "PI") {
        return 3.14159265358979323846;
    } else if (constantName == "E") {
        return 2.71828182845904523536;
    }
    return 0;
}

std::shared_ptr<Expression> Constant::simplify() {
    return shared_from_this();
}

bool Constant::openForInput() {
    return false;
}

std::string Constant::toString() {
    return constantName;
}

/* *************************************************************************************************** */

Variable::Variable(const std::string &variableName) : variableName(variableName) {
}

std::shared_ptr<Expression> Variable::add(std::shared_ptr<ASTNode> toAdd) {
    return std::make_shared<BinaryOperationExpression>(shared_from_this(), std::static_pointer_cast<Operation>(toAdd));
}

long double Variable::resolve(std::map<std::string, long double> vars) {
    return vars[variableName];
}

std::shared_ptr<Expression> Variable::simplify() {
    return shared_from_this();
}

bool Variable::openForInput() {
    return false;
}

std::string Variable::toString() {
    return variableName;
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
    if (nestedExp == nullptr) {
        nestedExp = std::static_pointer_cast<Expression>(toAdd);
    } else {
        if (std::dynamic_pointer_cast<Parenthesis>(toAdd) != nullptr && !nestedExp->openForInput()) {
            closed = true;
        } else {
            nestedExp = nestedExp->add(toAdd);
        }
    }
    return shared_from_this();
}

long double Parenthesis::resolve(std::map<std::string, long double> vars) {
    return nestedExp->resolve(vars);
}

std::shared_ptr<Expression> Parenthesis::simplify() {
    return nestedExp;
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
    return nestedExp ? "(" + nestedExp->toString() + ")" : "(?";
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

long double Operation::resolve(std::map<std::string, long double> vars, std::shared_ptr<Expression> op1,
                               std::shared_ptr<Expression> op2) {
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

PostfixOperation::PostfixOperation(const std::string &operatorName) : operatorName(operatorName) {
    std::transform(this->operatorName.begin(), this->operatorName.end(), this->operatorName.begin(), ::toupper);
}

std::shared_ptr<Expression> PostfixOperation::add(std::shared_ptr<ASTNode> toAdd) {
    std::shared_ptr<Expression> retExp = shared_from_this();
    if (nestedExp == nullptr) {
        nestedExp = std::static_pointer_cast<Expression>(toAdd);
    } else if (nestedExp->openForInput()) {
        nestedExp = nestedExp->add(toAdd);
    } else {
        retExp = std::make_shared<BinaryOperationExpression>(shared_from_this(), std::static_pointer_cast<Operation>(toAdd));
    }
    return retExp;
}

long double PostfixOperation::resolve(std::map<std::string, long double> vars) {
    if (operatorName == "SIN") {
        return sin(nestedExp->resolve(vars));
    } else if (operatorName == "COS") {
        return cos(nestedExp->resolve(vars));
    } else if (operatorName == "TAN") {
        return tan(nestedExp->resolve(vars));
    } else if (operatorName == "ASIN") {
        return asin(nestedExp->resolve(vars));
    } else if (operatorName == "ACOS") {
        return acos(nestedExp->resolve(vars));
    } else if (operatorName == "ATAN") {
        return atan(nestedExp->resolve(vars));
    } else if (operatorName == "SQRT") {
        return sqrt(nestedExp->resolve(vars));
    } else if (operatorName == "LOG") {
        return log(nestedExp->resolve(vars));
    } else if (operatorName == "LOGTEN") {
        return log10(nestedExp->resolve(vars));
    }
    return 0;
}

std::shared_ptr<Expression> PostfixOperation::simplify() {
    return shared_from_this();
}

bool PostfixOperation::openForInput() {
    return !nestedExp || nestedExp->openForInput();
}

void PostfixOperation::validate() {
 nestedExp->validate();
}

std::string PostfixOperation::toString() {
    return operatorName + "(" + nestedExp->toString() + ")";
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

