

#pragma once

#include <string>
#include <memory>
#include "TokenType.hpp"

class ASTNode;

class Token {
private:
    std::string data;
    TokenType tokenType;
public:
    Token(const std::string &data, TokenType tokenType);

    const std::string &getData() const;

    std::string getType() const;

    TokenType getTokenType() const;

    std::shared_ptr<ASTNode> toASTNode() const;

    std::string toString() const;
};
