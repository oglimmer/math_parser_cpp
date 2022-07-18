
#include "BinaryOperationExpression.hpp"
#include "tokenize/LexicalAnalyzer.hpp"
#include "InvalidFormulaException.hpp"


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
            auto binOp2 = ASTBuilder::getSelf()->createBinaryOperationExpression(op2, toAddOp, nullptr);
            return ASTBuilder::getSelf()->createBinaryOperationExpression(op1, op, binOp2);
        } else {
            return ASTBuilder::getSelf()->createBinaryOperationExpression(shared_from_this(), toAddOp, nullptr);
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