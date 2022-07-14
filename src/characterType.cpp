#include "characterType.hpp"
#include "ast/Constant.hpp"
#include "ast/Operation.hpp"
#include "ast/PostfixOperation.hpp"
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

bool containsKeyword(const std::string& str) {
    return ConstantEnum::match(str) || PostfixOperationEnum::match(str);
}

bool containsConstant(const std::string& str) {
    return ConstantEnum::match(str);
}
