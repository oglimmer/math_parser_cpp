

#include "Constant.hpp"

#include "tokenize/LexicalAnalyzer.hpp"
#include "BinaryOperationExpression.hpp"
#include "InvalidFormulaException.hpp"

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