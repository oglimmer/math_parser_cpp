
#pragma once

#include "Expression.hpp"

class Variable : public Expression, public std::enable_shared_from_this<Variable> {
private:
    std::string variableName;
public:
    Variable(const std::string &variableName);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) override;

    long double resolve(std::map<std::string, long double> vars) const override;

    std::shared_ptr<Expression> simplify() override;

    bool openForInput() const override;

    std::string toString() const override;
};