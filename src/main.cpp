#include <iostream>
#include <string>

#include "tokenize/LexicalAnalyzer.hpp"
#include "FunctionParser.hpp"
#include "InvalidFormulaException.hpp"
#include "ast/Expression.hpp"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "usage: you need to pass at least one parameter" << std::endl;
        return EXIT_FAILURE;
    }

    std::map<std::string, long double> vars;
    for (int i = 2; i + 1 < argc; i += 2) {
        std::string varName(argv[i]);
        long double varValue = std::stold(argv[i + 1]);
        vars.insert(std::pair<std::string, long double>(varName, varValue));
    }

    try {
        std::string input(argv[1]);
        FunctionParser functionParser;
        auto tokens = functionParser.tokenize(input);
        auto expression = functionParser.tokensToExpression(tokens);
        std::cout.precision(34);
        std::cout << expression->resolve(vars) << std::endl;
    } catch (const InvalidFormulaException &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
