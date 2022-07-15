
#pragma once

#include "Expression.hpp"


#define PARENTHESIS_CHAR_OPEN '('
#define PARENTHESIS_CHAR_CLOSE ')'

class Parenthesis : public Expression, public std::enable_shared_from_this<Parenthesis> {
private:
    std::shared_ptr<Expression> nestedExp;
    bool closed;
    char c;
public:
    Parenthesis(char c);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) override;

    long double resolve(std::map<std::string, long double> vars) const override;

    std::shared_ptr<Expression> simplify() override;

    bool openForInput() const override;

    void validate() const override;

    std::string toString() const override;
};