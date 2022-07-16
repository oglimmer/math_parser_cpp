#include "characterType.hpp"
#include <cctype>

bool isAlphabetic(char c) {
    return std::isalpha(c);
}

bool isNumber(char c) {
    return std::isalnum(c) || c == '.';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
}

bool isAlgebraicSign(char c) {
    return c == '+' || c == '-';
}

bool isBracket(char c) {
    return c == '(' || c == ')';
}

bool containsKeyword(const std::string& str) {
    return str == "pi" || str == "e";
}

bool containsConstant(const std::string& str) {
    return str == "pi" || str == "e";
}
