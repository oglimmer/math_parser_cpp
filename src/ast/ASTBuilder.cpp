
#include "ASTBuilder.hpp"
#include "ASTNode.hpp"
#include "Expression.hpp"
#include <algorithm>

#include "tokenize/Token.hpp"
#include "Number.hpp"
#include "Operation.hpp"
#include "Parenthesis.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "PostfixOperation.hpp"
#include "BinaryOperationExpression.hpp"

std::shared_ptr<Expression> ASTBuilder::tokensToExpression(const std::vector<std::shared_ptr<Token>> &tokens) const {
    std::shared_ptr<Expression> resultExp;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        const std::shared_ptr<Token> &token = *it;
        std::shared_ptr<ASTNode> astNode = toASTNode(token->getTokenType(), token->getData());
        if (!resultExp) {
            resultExp = std::static_pointer_cast<Expression>(astNode);
        } else {
            resultExp = resultExp->add(astNode);
        }
    }
    resultExp->validate();
    return resultExp->simplify();
}

std::shared_ptr<ASTNode> ASTBuilder::toASTNode(TokenType tokenType, std::string data) const {
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

std::shared_ptr<BinaryOperationExpression> ASTBuilder::createBinaryOperationExpression(
        std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op, std::shared_ptr<Expression> op2) const {
    if (op2 != nullptr) {
        return std::make_shared<BinaryOperationExpression>(op1, op, op2);
    } else {
        return std::make_shared<BinaryOperationExpression>(op1, op);
    }
}

std::shared_ptr<ASTBuilder> ASTBuilder::self = std::shared_ptr<ASTBuilder>(new ASTBuilder());

std::shared_ptr<ASTBuilder> ASTBuilder::getSelf() {
    return ASTBuilder::self;
}

void ASTBuilder::initImpl(std::shared_ptr<ASTBuilder> impl) {
    ASTBuilder::self = impl;
}