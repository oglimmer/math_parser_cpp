
#include "Number.hpp"

#include "BinaryOperationExpression.hpp"

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