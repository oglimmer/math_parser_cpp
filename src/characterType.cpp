#include "characterType.hpp"
#include <cctype>

bool isAlphabetic(char c) {
    return std::isalpha(c);
}

bool isNumber(char c) {
    return std::isdigit(c) || c == '.';
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
    return str == "pi" || str == "e" || str == "sin" || str == "cos" || str == "tan" || str == "asin" || str == "acos" || str == "atan" || str == "sqrt" || str == "log" || str == "logten";
}

bool containsConstant(const std::string& str) {
    return str == "pi" || str == "e";
}
