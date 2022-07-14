

TEST_CASE("testing FunctionParser - simple variable") {
    FunctionParser functionParser;
    std::map<std::string, long double> vars;
    vars.insert(std::pair<std::string, long double>("x", 3));
    auto result = functionParser.debugResolve("x", vars);
    CHECK(result == 3);
}


TEST_CASE("testing FunctionParser - simple variable") {
    FunctionParser functionParser;
    std::map<std::string, long double> vars;
    vars.insert(std::pair<std::string, long double>("x", 3));
    vars.insert(std::pair<std::string, long double>("xx", 33));
    auto result = functionParser.debugResolve("x+xx", vars);
    CHECK(result == 36);
}

