
#include "Parenthesis.hpp"
#include "Operation.hpp"
#include "tokenize/LexicalAnalyzer.hpp"
#include "BinaryOperationExpression.hpp"
#include "InvalidFormulaException.hpp"

Parenthesis::Parenthesis(char c) : c(c), closed(false) {
}

std::shared_ptr<Expression> Parenthesis::add(std::shared_ptr<ASTNode> toAdd) {
    if (closed) {
        auto toAddOp = std::dynamic_pointer_cast<Operation>(toAdd);
        if (!toAddOp) {
            // TODO: this must never happen. Error is actually LexicalAnalyzer.
            throw InvalidFormulaException("Missing opening (");
        }
        return ASTBuilder::getSelf()->createBinaryOperationExpression(shared_from_this(), toAddOp, nullptr);
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
    return nestedExp->simplify();
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