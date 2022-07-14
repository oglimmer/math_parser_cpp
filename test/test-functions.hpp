
TEST_CASE("testing function isBracket") {
    CHECK(isBracket('(') == true);
    CHECK(isBracket('a') == false);
}
