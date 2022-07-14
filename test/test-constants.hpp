

TEST_CASE("testing FunctionParser - pi and e") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("pi*e");
    CHECK(result == doctest::Approx(8.5397));
}

