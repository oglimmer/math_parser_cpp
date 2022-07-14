
#pragma once


#include <string>
#include <map>
#include <memory>
#include <vector>

class Token;

class Expression;

class FunctionParser {
public:
    std::unique_ptr<std::vector<std::shared_ptr<Token>>> tokenize(const std::string &input) const;

    std::shared_ptr<Expression> tokensToExpression(const std::unique_ptr<std::vector<std::shared_ptr<Token>>> &tokens) const;

    long double debugResolve(const std::string &input, std::map<std::string, long double> vars = std::map<std::string, long double>()) const;

private:
    std::shared_ptr<Expression> debugParse(const std::string &input) const;

    void debugOutput(const std::unique_ptr<std::vector<std::shared_ptr<Token>>> &tokens) const;
};

