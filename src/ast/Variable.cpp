
#include "Variable.hpp"
#include "Operation.hpp"
#include "BinaryOperationExpression.hpp"

Variable::Variable(const std::string &variableName) : variableName(variableName) {
}

std::shared_ptr<Expression> Variable::add(std::shared_ptr<ASTNode> toAdd) {
    return ASTBuilder::getSelf()->createBinaryOperationExpression(shared_from_this(),
                                                                  std::static_pointer_cast<Operation>(toAdd),
                                                                  nullptr);
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