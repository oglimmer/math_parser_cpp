
#include "ASTBuilder.hpp"
#include "ASTNode.hpp"
#include "Expression.hpp"
#include <algorithm>

#include "tokenize/Token.hpp"

std::shared_ptr<Expression> ASTBuilder::tokensToExpression(const std::vector<std::shared_ptr<Token>> &tokens) const {
    std::shared_ptr<Expression> resultExp;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        const std::shared_ptr<Token> &token = *it;
        std::shared_ptr<ASTNode> astNode = token->toASTNode();
        if (!resultExp) {
            resultExp = std::static_pointer_cast<Expression>(astNode);
        } else {
            resultExp = resultExp->add(astNode);
        }
    }
    resultExp->validate();
    return resultExp->simplify();
}

