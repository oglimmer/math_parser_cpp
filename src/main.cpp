#include <iostream>
#include <string>

#include "characterType.hpp"
#include "LexicalAnalyzer.hpp"
#include "FunctionParser.hpp"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "usage: you need to pass at least one parameter" << std::endl;
        return EXIT_FAILURE;
    }

    std::string input(argv[1]);
    std::cout << "Input: " << input << std::endl;

    std::map<std::string, long double> vars;
    for (int i = 2; i + 1 < argc; i += 2) {
        std::string varName(argv[i]);
        long double varValue = std::stold(argv[i + 1]);
        vars.insert(std::pair<std::string, long double>(varName, varValue));
    }

    FunctionParser functionParser;
    auto result = functionParser.parse(input, vars);
    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
