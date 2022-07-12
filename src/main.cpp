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

    FunctionParser functionParser;
    auto result = functionParser.parse(input);
    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
