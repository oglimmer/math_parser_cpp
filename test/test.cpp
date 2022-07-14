
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include "characterType.hpp"
#include "tokenize/LexicalAnalyzer.hpp"
#include "tokenize/Token.hpp"
#include "InvalidFormulaException.hpp"
#include "FunctionParser.hpp"


#include "test-constants.hpp"
#include "test-variables.hpp"
#include "test-postfixoperators.hpp"
#include "test-parenthesis.hpp"
#include "test-operators.hpp"
#include "test-LexicalAnalyzer.hpp"
#include "test-functions.hpp"
#include "test-errors.hpp"
