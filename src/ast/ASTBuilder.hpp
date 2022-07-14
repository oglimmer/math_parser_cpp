#pragma once


#include <vector>
#include <memory>


class Token;

class Expression;

class ASTBuilder {
public:
    std::shared_ptr<Expression> tokensToExpression(const std::vector<std::shared_ptr<Token>> &tokens) const;

};
