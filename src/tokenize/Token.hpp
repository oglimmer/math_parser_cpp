

#pragma once

#include <string>
#include "ast/ASTNode.hpp"

#include <memory>

enum TokenType {
    NUMBER, OPERATOR, PARENTHESIS_OPEN, PARENTHESIS_CLOSE, CONSTANT, VARIABLE, POSTFIX_OPERATOR
};


class Token {
private:
    std::string data;
    TokenType tokenType;
public:
    Token(const std::string &data, TokenType tokenType);

    const std::string &getData() const;

    std::shared_ptr<ASTNode> toASTNode() const;

    std::string toString() const;
};
