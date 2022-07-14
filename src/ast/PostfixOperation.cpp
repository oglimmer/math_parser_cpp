
#include "PostfixOperation.hpp"
#include "tokenize/LexicalAnalyzer.hpp"
#include "math.h"
#include "BinaryOperationExpression.hpp"
#include "Operation.hpp"
#include "InvalidFormulaException.hpp"
#include <memory>


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
