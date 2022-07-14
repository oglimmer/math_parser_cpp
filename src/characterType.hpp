#pragma once

#include <iostream>
#include <string>

bool isAlphabetic(char c);

bool isDigit(char c);

bool isOperator(char c);

bool isAlgebraicSign(char c);

bool isBracket(char c);

bool containsKeyword(const std::string& str);

bool containsConstant(const std::string& str);
