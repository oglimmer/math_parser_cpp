

TEST_CASE("testing FunctionParser - parenthesis") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("(2)");
    CHECK(result == 2);
}

TEST_CASE("testing FunctionParser - tripple parenthesis") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("(((2)))");
    CHECK(result == 2);
}

TEST_CASE("testing FunctionParser - parenthesis and addition") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("(2+3)");
    CHECK(result == 5);
}

TEST_CASE("testing FunctionParser - parenthesis and addition and multiplication") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("(2+3)*3");
    CHECK(result == 15);
}

TEST_CASE("testing FunctionParser - parenthesis and addition and multiplication2") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("3*(2+3)");
    CHECK(result == 15);
}

TEST_CASE("testing FunctionParser - double parenthesis and addition and multiplication") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("3*(2*(2+3)+3)");
    CHECK(result == 39);
}

TEST_CASE("testing FunctionParser - power and multiplication and parenthesis") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("4*3^(4*2)*2");
    CHECK(result == 52488);
}

