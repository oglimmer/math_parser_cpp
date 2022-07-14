#pragma once

#include "Expression.hpp"

class Number : public Expression, public std::enable_shared_from_this<Number> {
private:
    long double val;
public:
    Number(long double val);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve(std::map<std::string, long double> vars) const;

    std::shared_ptr<Expression> simplify();

    bool openForInput() const;

    std::string toString() const;
};
