
#include "Token.hpp"

#include "ast/Number.hpp"
#include "ast/Operation.hpp"
#include "ast/Parenthesis.hpp"
#include "ast/Constant.hpp"
#include "ast/Variable.hpp"
#include "ast/PostfixOperation.hpp"
#include "ast/ASTNode.hpp"


Token::Token(const std::string &data, TokenType tokenType) : data(data), tokenType(tokenType) {}

const std::string &Token::getData() const {
    return data;
}

TokenType Token::getTokenType() const {
    return tokenType;
}

std::string Token::getType() const {
    std::string typeStr;
    switch (tokenType) {
        case TokenType::NUMBER:
            typeStr = "NUMBER";
            break;
        case TokenType::OPERATOR:
            typeStr = "OPERATOR";
            break;
        case TokenType::PARENTHESIS_OPEN:
            typeStr = "PARENTHESIS_OPEN";
            break;
        case TokenType::PARENTHESIS_CLOSE:
            typeStr = "PARENTHESIS_CLOSE";
            break;
        case TokenType::CONSTANT:
            typeStr = "CONSTANT";
            break;
        case TokenType::VARIABLE:
            typeStr = "VARIABLE";
            break;
        case TokenType::POSTFIX_OPERATOR:
            typeStr = "POSTFIX_OPERATOR";
            break;
    }
    return typeStr;
}

std::string Token::toString() const {
    return "{type:" + getType() + ", data:'" + data + "'}";
}


