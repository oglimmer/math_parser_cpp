
#pragma once


#include <string>
#include <map>

class FunctionParser {
public:
    long double parse(const std::string &input);
    long double parse(const std::string &input, std::map<std::string, long double> vars);
};

