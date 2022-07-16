
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include "characterType.cpp"
#include "LexicalAnalyzer.hpp"
#include "FunctionParser.hpp"

TEST_CASE("testing functions") {
    CHECK(isBracket('(') == true);
    CHECK(isBracket('a') == false);
}

TEST_CASE("testing LexicalAnalyzer - simple number") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("2");
    CHECK(tokensToTest->at(0)->getData() == "2");
    CHECK(tokensToTest->size() == 1);
}

TEST_CASE("testing LexicalAnalyzer - floating point number") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("2.1");
    CHECK(tokensToTest->at(0) == "2.1");
    CHECK(tokensToTest->size() == 1);
}

TEST_CASE("testing LexicalAnalyzer - large floating point number") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("234.354"); 
    CHECK(tokensToTest->at(0) == "234.354");
    CHECK(tokensToTest->size() == 1);
}

TEST_CASE("testing LexicalAnalyer - addition with two floating point numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("23.4+435.1");
    CHECK(tokensToTest->at(0) == "23.4");
    CHECK(tokensToTest->at(1) == "+");
    CHECK(tokensToTest->at(2) == "435.1");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing LexicalAnalyer - addition with three floating point numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("345.1+2.1+3456.56");
    CHECK(tokensToTest->at(0) == "345.1");
    CHECK(tokensToTest->at(1) == "+");
    CHECK(tokensToTest->at(2) == "2.1");
    CHECK(tokensToTest->at(3) == "+");
    CHECK(tokensToTest->at(4) == "3456.56");
    CHECK(tokensToTest->size() == 5);
}



TEST_CASE("testing LexicalAnalyzer - simple addition") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("2+3");
    CHECK(tokensToTest->at(0)->getData() == "2");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "3");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing LexicalAnalyzer - addition with large numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("258+37375");
    CHECK(tokensToTest->at(0)->getData() == "258");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "37375");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing LexicalAnalyzer - addition with multiple numbers") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("258+37375+433");
    CHECK(tokensToTest->at(0)->getData() == "258");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "37375");
    CHECK(tokensToTest->at(3)->getData() == "+");
    CHECK(tokensToTest->at(4)->getData() == "433");
    CHECK(tokensToTest->size() == 5);
}

TEST_CASE("testing LexicalAnalyzer - addition with multiple decimals") {
    LexicalAnalyzer lexicalAnalyzer;
    auto tokensToTest = lexicalAnalyzer.parseToTokens("34.56+123.89");
    CHECK(tokensToTest->at(0)->getData() == "34.56");
    CHECK(tokensToTest->at(1)->getData() == "+");
    CHECK(tokensToTest->at(2)->getData() == "123.89");
    CHECK(tokensToTest->size() == 3);
}

TEST_CASE("testing FunctionParser - decimal addition and subtraction") {
    FunctionParser functionParser;
    auto result = functionParser.parse("34.56+123.89-32.75");
    CHECK(result == 125.69999999999999);
}

TEST_CASE("testing FunctionParser - addition and multiplication") {
    FunctionParser functionParser;
    auto result = functionParser.parse("1+2*3");
    CHECK(result == 7);
}

TEST_CASE("testing FunctionParser - multiplication and addition") {
    FunctionParser functionParser;
    auto result = functionParser.parse("2*3+1");
    CHECK(result == 7);
}

TEST_CASE("testing FunctionParser - multiplication and division") {
    FunctionParser functionParser;
    auto result = functionParser.parse("4*3/2");
    CHECK(result == 6);
}

TEST_CASE("testing FunctionParser - power") {
    FunctionParser functionParser;
    auto result = functionParser.parse("2*3^4");
    CHECK(result == 162);
}

TEST_CASE("testing FunctionParser - parenthesis") {
    FunctionParser functionParser;
    auto result = functionParser.parse("(2)");
    CHECK(result == 2);
}

TEST_CASE("testing FunctionParser - parenthesis and addition") {
    FunctionParser functionParser;
    auto result = functionParser.parse("(2+3)");
    CHECK(result == 5);
}

TEST_CASE("testing FunctionParser - parenthesis and addition and multiplication") {
    FunctionParser functionParser;
    auto result = functionParser.parse("(2+3)*3");
    CHECK(result == 15);
}

TEST_CASE("testing FunctionParser - parenthesis and addition and multiplication2") {
    FunctionParser functionParser;
    auto result = functionParser.parse("3*(2+3)");
    CHECK(result == 15);
}
