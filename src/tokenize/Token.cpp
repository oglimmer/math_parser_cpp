
#include "Token.hpp"

#include "ast/Number.hpp"
#include "ast/Operation.hpp"
#include "ast/Parenthesis.hpp"
#include "ast/Constant.hpp"
#include "ast/Variable.hpp"
#include "ast/PostfixOperation.hpp"


Token::Token(const std::string &data, TokenType tokenType) : data(data), tokenType(tokenType) {}

const std::string &Token::getData() const {
    return data;
}

std::shared_ptr<ASTNode> Token::toASTNode() const {
    switch (tokenType) {
        case TokenType::NUMBER:
            return std::make_shared<Number>(std::stold(data));
        case TokenType::OPERATOR:
            return std::make_shared<Operation>(data[0]);
        case TokenType::PARENTHESIS_OPEN:
        case TokenType::PARENTHESIS_CLOSE:
            return std::make_shared<Parenthesis>(data[0]);
        case TokenType::CONSTANT:
            return std::make_shared<Constant>(data);
        case TokenType::VARIABLE:
            return std::make_shared<Variable>(data);
        case TokenType::POSTFIX_OPERATOR:
            return std::make_shared<PostfixOperation>(data);
    }
    return nullptr;
}

std::string Token::toString() const {
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
    return "{type:" + typeStr + ", data:'" + data + "'}";
}

