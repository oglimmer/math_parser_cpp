



TEST_CASE("testing FunctionParser - decimal addition and subtraction") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("34.56+123.89-32.75");
    CHECK(result == doctest::Approx(125.7));
}

TEST_CASE("testing FunctionParser - addition and multiplication") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("1+2*3");
    CHECK(result == 7);
}

TEST_CASE("testing FunctionParser - multiplication and addition") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("2*3+1");
    CHECK(result == 7);
}

TEST_CASE("testing FunctionParser - multiplication and division") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("4*3/2");
    CHECK(result == 6);
}

TEST_CASE("testing FunctionParser - multiplication and power") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("2*3^4");
    CHECK(result == 162);
}

TEST_CASE("testing FunctionParser - power and multiplication") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("3^4*2");
    CHECK(result == 162);
}

TEST_CASE("testing FunctionParser - negative numbers") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("-3--3+-3");
    CHECK(result == -3);
}

