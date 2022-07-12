
#include "FunctionParser.hpp"
#include "LexicalAnalyzer.hpp"


long double FunctionParser::parse(const std::string &input) {
    LexicalAnalyzer lexicalAnalyzer;
    std::unique_ptr<std::vector<std::shared_ptr<Token>>> tokens = lexicalAnalyzer.parseToTokens(input);

    std::cout << "Tokens: [";
    for (auto i = tokens->begin(); i != tokens->end(); ++i) {
        if (i != tokens->begin()) {
            std::cout << ',';
        }
        std::cout << (*i)->getData();
    }
    std::cout << "]" << std::endl;

    ASTBuilder astBuilder;
    auto expression = astBuilder.tokensToExpression(*tokens);
    std::cout << "Expression: " << expression->toString() << std::endl;
    return expression->resolve();
}