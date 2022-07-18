#pragma once

#include "Expression.hpp"

class Number : public Expression, public std::enable_shared_from_this<Number> {
protected:
    long double val;
public:
    Number(long double val);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) override;

    long double resolve(std::map<std::string, long double> vars) const override;

    std::shared_ptr<Expression> simplify() override;

    bool openForInput() const override;

    std::string toString() const override;
};
