

TEST_CASE("testing FunctionParser - postoperator") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve(
            "sin(1)*cos(2)*tan(3)*asin(.1)*acos(.2)*atan(.3)*sqrt(7)*log(8)*logten(9)");
    CHECK(result == doctest::Approx(0.0104771));    
}

TEST_CASE("testing FunctionParser - sqrt") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("sqrt(3+3+3)");
    CHECK(result == 3);
}

TEST_CASE("testing FunctionParser - trigonometry") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("sin(2)*cos(3)*tan(4)");
    CHECK(result == doctest::Approx(-1.04227));
}

TEST_CASE("testing FunctionParser - asin") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("2*asin(1)-pi");
    CHECK(result == doctest::Approx(0));    
}

TEST_CASE("testing FunctionParser - log") {
    FunctionParser functionParser;
    auto result = functionParser.debugResolve("log(3)*logten(4)");
    CHECK(result == doctest::Approx(0.661431));        
}

