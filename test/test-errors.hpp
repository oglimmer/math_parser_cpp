

TEST_CASE("testing FunctionParser - missing (") {
    FunctionParser functionParser;
    CHECK_THROWS_WITH_AS(functionParser.debugResolve("2+3)"), "Missing opening (", InvalidFormulaException);
}

TEST_CASE("testing FunctionParser - missing )") {
    FunctionParser functionParser;
    CHECK_THROWS_WITH_AS(functionParser.debugResolve("(2+3"), "Missing closing )", InvalidFormulaException);
}

TEST_CASE("testing FunctionParser - starting with operator") {
    FunctionParser functionParser;
    CHECK_THROWS_WITH_AS(functionParser.debugResolve("/3"), "Invalid character found /", InvalidFormulaException);
}

TEST_CASE("testing FunctionParser - duplicated operator") {
    FunctionParser functionParser;
    CHECK_THROWS_WITH_AS(functionParser.debugResolve("2+3**4"), "Invalid character found *", InvalidFormulaException);
}

TEST_CASE("testing FunctionParser - division by zero") {
    FunctionParser functionParser;
    CHECK(std::isinf(functionParser.debugResolve("1/0")));
}
