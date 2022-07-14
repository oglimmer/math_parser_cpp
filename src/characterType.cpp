#include "characterType.hpp"
#include "ASTBuilder.hpp"
#include <cctype>

bool isAlphabetic(char c) {
    return std::isalpha(c);
}

bool isDigit(char c) {
    return std::isdigit(c) || c == '.';
}

bool isOperator(char c) {
    return Operation::match(c);
}

bool isAlgebraicSign(char c) {
    return c == '+' || c == '-';
}

bool isBracket(char c) {
    return c == PARENTHESIS_CHAR_OPEN || c == PARENTHESIS_CHAR_CLOSE;
}

bool containsKeyword(const std::string& str) {
    return ConstantEnum::match(str) || PostfixOperationEnum::match(str);
}

bool containsConstant(const std::string& str) {
    return ConstantEnum::match(str);
}
