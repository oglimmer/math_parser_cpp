
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

long double BinaryOperationExpression::resolve(std::map<std::string, long double> vars) const {
    return op->resolve(vars, op1, op2);
}

std::shared_ptr<Expression> BinaryOperationExpression::simplify() {
    return shared_from_this();
}

void BinaryOperationExpression::validate() const {
    if (!op2) {
        throw InvalidFormulaException("op2 must not be null");
    }
    op1->validate();
    op2->validate();
}

bool BinaryOperationExpression::openForInput() const {
    return !op2 || op2->openForInput();
}

std::string BinaryOperationExpression::toString() const {
    return "(" + op1->toString() + op->toString() + op2->toString() + ")";
}

/* *************************************************************************************************** */

Number::Number(long double val) : val(val) {
}

std::shared_ptr<Expression> Number::add(std::shared_ptr<ASTNode> toAdd) {
    return std::make_shared<BinaryOperationExpression>(shared_from_this(), std::static_pointer_cast<Operation>(toAdd));
}

long double Number::resolve(std::map<std::string, long double> vars) const {
    return val;
}

std::shared_ptr<Expression> Number::simplify() {
    return shared_from_this();
}

bool Number::openForInput() const {
    return false;
}

std::string Number::toString() const {
    return std::to_string(val);
}

/* *************************************************************************************************** */

ConstantEnum ConstantEnum::PI("pi", 3.14159265358979323846);
ConstantEnum ConstantEnum::E("e", 2.71828182845904523536);
ConstantEnum ConstantEnum::ALL[] = {PI, E};

ConstantEnum::ConstantEnum(const std::string &name, long double val) : name(name), val(val) {
}

ConstantEnum &ConstantEnum::byName(const std::string &name) {
    for (auto &obj: ConstantEnum::ALL) {
        if (obj.name == name) {
            return obj;
        }
    }
    throw InvalidFormulaException("Unknown postfix constant " + name);
}

bool ConstantEnum::match(const std::string &name) {
    for (auto &obj: ConstantEnum::ALL) {
        if (obj.name == name) {
            return true;
        }
    }
    return false;
}

const std::string &ConstantEnum::getName() const {
    return name;
}

long double ConstantEnum::getValue() const {
    return val;
}


Constant::Constant(const std::string &constantName) : constantImpl(ConstantEnum::byName(constantName)) {
}

std::shared_ptr<Expression> Constant::add(std::shared_ptr<ASTNode> toAdd) {
    return std::make_shared<BinaryOperationExpression>(shared_from_this(), std::static_pointer_cast<Operation>(toAdd));
}

long double Constant::resolve(std::map<std::string, long double> vars) const {
    return constantImpl.getValue();
}

std::shared_ptr<Expression> Constant::simplify() {
    return shared_from_this();
}

bool Constant::openForInput() const {
    return false;
}

std::string Constant::toString() const {
    return constantImpl.getName();
}

/* *************************************************************************************************** */

Variable::Variable(const std::string &variableName) : variableName(variableName) {
}

std::shared_ptr<Expression> Variable::add(std::shared_ptr<ASTNode> toAdd) {
    return std::make_shared<BinaryOperationExpression>(shared_from_this(), std::static_pointer_cast<Operation>(toAdd));
}

long double Variable::resolve(std::map<std::string, long double> vars) const {
    return vars[variableName];
}

std::shared_ptr<Expression> Variable::simplify() {
    return shared_from_this();
}

bool Variable::openForInput() const {
    return false;
}

std::string Variable::toString() const {
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
            throw InvalidFormulaException("Missing opening (");
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

long double Parenthesis::resolve(std::map<std::string, long double> vars) const {
    return nestedExp->resolve(vars);
}

std::shared_ptr<Expression> Parenthesis::simplify() {
    return nestedExp;
}

bool Parenthesis::openForInput() const {
    return !closed;
}

void Parenthesis::validate() const {
    if (c == ')') {
        throw InvalidFormulaException("Missing opening (");
    } else if (!closed) {
        throw InvalidFormulaException("Missing closing )");
    }
    nestedExp->validate();
}

std::string Parenthesis::toString() const {
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

/* *************************************************************************************************** */

PostfixOperationEnum PostfixOperationEnum::SIN("sin", sin);
PostfixOperationEnum PostfixOperationEnum::COS("cos", cos);
PostfixOperationEnum PostfixOperationEnum::TAN("tan", tan);
PostfixOperationEnum PostfixOperationEnum::ASIN("asin", asin);
PostfixOperationEnum PostfixOperationEnum::ACOS("acos", acos);
PostfixOperationEnum PostfixOperationEnum::ATAN("atan", atan);
PostfixOperationEnum PostfixOperationEnum::SQRT("sqrt", sqrt);
PostfixOperationEnum PostfixOperationEnum::LOG("log", log);
PostfixOperationEnum PostfixOperationEnum::LOGTEN("logten", log10);
PostfixOperationEnum PostfixOperationEnum::ALL[] = {SIN, COS, TAN, ASIN, ACOS, ATAN, SQRT, LOG, LOGTEN};

PostfixOperationEnum &PostfixOperationEnum::byName(const std::string &name) {
    for (auto &obj: PostfixOperationEnum::ALL) {
        if (obj.name == name) {
            return obj;
        }
    }
    throw InvalidFormulaException("Unknown postfix operator " + name);
}

bool PostfixOperationEnum::match(const std::string &name) {
    for (auto &obj: PostfixOperationEnum::ALL) {
        if (obj.name == name) {
            return true;
        }
    }
    return false;
}

const std::string &PostfixOperationEnum::getName() const {
    return name;
}

FuncPtrToTrigonometry PostfixOperationEnum::getFuncPtrOne() const {
    return functionPointer;
}

PostfixOperation::PostfixOperation(const std::string &operatorName) : postfixOperationImpl(
        PostfixOperationEnum::byName(operatorName)) {
}

std::shared_ptr<Expression> PostfixOperation::add(std::shared_ptr<ASTNode> toAdd) {
    std::shared_ptr<Expression> retExp = shared_from_this();
    if (!nestedExp) {
        nestedExp = std::static_pointer_cast<Expression>(toAdd);
    } else if (nestedExp->openForInput()) {
        nestedExp = nestedExp->add(toAdd);
    } else {
        retExp = std::make_shared<BinaryOperationExpression>(shared_from_this(),
                                                             std::static_pointer_cast<Operation>(toAdd));
    }
    return retExp;
}

long double PostfixOperation::resolve(std::map<std::string, long double> vars) const {
    return postfixOperationImpl.getFuncPtrOne()(nestedExp->resolve(vars));
}

std::shared_ptr<Expression> PostfixOperation::simplify() {
    return shared_from_this();
}

bool PostfixOperation::openForInput() const {
    return !nestedExp || nestedExp->openForInput();
}

void PostfixOperation::validate() const {
    nestedExp->validate();
}

std::string PostfixOperation::toString() const {
    return postfixOperationImpl.getName() + "(" + nestedExp->toString() + ")";
}


/* *************************************************************************************************** */

std::shared_ptr<Expression> ASTBuilder::tokensToExpression(const std::vector<std::shared_ptr<Token>> &tokens) const {
    std::shared_ptr<Expression> resultExp;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        const std::shared_ptr<Token> &token = *it;
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

