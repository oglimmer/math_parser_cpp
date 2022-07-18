#pragma once


#include <vector>
#include <memory>
#include "ASTNode.hpp"
#include "tokenize/TokenType.hpp"

class Token;

class Expression;

class Operation;

class BinaryOperationExpression;


class ASTBuilder {
private:
    static std::shared_ptr<ASTBuilder> self;
public:
    static std::shared_ptr<ASTBuilder> getSelf();
    static void initImpl(std::shared_ptr<ASTBuilder> impl);
protected:
    ASTBuilder() {}
public:
    std::shared_ptr<Expression> tokensToExpression(const std::vector<std::shared_ptr<Token>> &tokens) const;

    virtual std::shared_ptr<ASTNode> toASTNode(TokenType tokenType, std::string data) const;

    virtual std::shared_ptr<BinaryOperationExpression> createBinaryOperationExpression(
            std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op, std::shared_ptr<Expression> op2) const;
};
