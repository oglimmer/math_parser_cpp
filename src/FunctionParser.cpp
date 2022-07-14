
#include "FunctionParser.hpp"

#include "tokenize/LexicalAnalyzer.hpp"
#include "tokenize/Token.hpp"
#include "ast/Expression.hpp"

#include <iostream>

std::unique_ptr<std::vector<std::shared_ptr<Token>>> FunctionParser::tokenize(const std::string &input) const {
    LexicalAnalyzer lexicalAnalyzer;
    return lexicalAnalyzer.parseToTokens(input);
}

std::shared_ptr<Expression> FunctionParser::tokensToExpression(const std::unique_ptr<std::vector<std::shared_ptr<Token>>>& tokens) const {
    ASTBuilder astBuilder;
    return astBuilder.tokensToExpression(*tokens);
}

std::shared_ptr<Expression> FunctionParser::debugParse(const std::string &input) const {
    std::unique_ptr<std::vector<std::shared_ptr<Token>>> tokens = tokenize(input);
    debugOutput(tokens);

    std::shared_ptr<Expression> expression = tokensToExpression(tokens);
    std::cout << "Expression: " << expression->toString() << std::endl;

    return expression;
}

long double FunctionParser::debugResolve(const std::string &input, std::map<std::string, long double> vars) const {
    return debugParse(input)->resolve(vars);
}

void FunctionParser::debugOutput(const std::unique_ptr<std::vector<std::shared_ptr<Token>>> &tokens) const {
    std::cout << "Tokens: [";
    for (auto it = tokens->begin(); it != tokens->end(); ++it) {
        if (it != tokens->begin()) {
            std::cout << ',';
        }
        std::cout << (*it)->toString();
    }
    std::cout << "]" << std::endl;
}
