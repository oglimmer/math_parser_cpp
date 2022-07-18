
#pragma once

#include "Expression.hpp"
#include <string>


typedef long double (*FuncPtrToTrigonometry)(long double);

class PostfixOperationEnum {
private:
    std::string name;
    FuncPtrToTrigonometry functionPointer;

    static PostfixOperationEnum SIN;
    static PostfixOperationEnum COS;
    static PostfixOperationEnum TAN;
    static PostfixOperationEnum ASIN;
    static PostfixOperationEnum ACOS;
    static PostfixOperationEnum ATAN;
    static PostfixOperationEnum SQRT;
    static PostfixOperationEnum LOG;
    static PostfixOperationEnum LOGTEN;
    static PostfixOperationEnum ALL[];

    PostfixOperationEnum(const std::string &name, FuncPtrToTrigonometry functionPointer)
            : name(name), functionPointer(functionPointer) {
    }

public:

    const std::string &getName() const;

    FuncPtrToTrigonometry getFuncPtrOne() const;

    static PostfixOperationEnum &byName(const std::string &name);

    static bool match(const std::string &name);
};

class PostfixOperation : public Expression, public std::enable_shared_from_this<PostfixOperation> {
protected:
    std::shared_ptr<Expression> nestedExp;
    PostfixOperationEnum postfixOperationImpl;
public:
    PostfixOperation(const std::string &operatorName);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) override;

    long double resolve(std::map<std::string, long double> vars) const override;

    std::shared_ptr<Expression> simplify() override;

    bool openForInput() const override;

    void validate() const override;

    std::string toString() const override;
};