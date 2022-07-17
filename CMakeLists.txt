cmake_minimum_required(VERSION 3.13)
set(project_name math_parser)

project(${project_name})

set(CMAKE_CXX_STANDARD 20)

find_package(doctest REQUIRED)
if(doctest_FOUND)
    message(STATUS "Found doctest")
else()
    message(FATAL_ERROR "Could not find doctest")
endif()

## lib

add_library(${project_name}-lib
        src/characterType.cpp
        src/tokenize/LexicalAnalyzer.cpp
        src/ast/ASTBuilder.cpp
        src/FunctionParser.cpp
        src/ast/ASTNode.cpp
        src/ast/Expression.cpp
        src/ast/BinaryOperationExpression.cpp
        src/ast/Number.cpp
        src/ast/Constant.cpp
        src/ast/Operation.cpp
        src/ast/Parenthesis.cpp
        src/ast/PostfixOperation.cpp
        src/ast/Variable.cpp
        src/tokenize/CharacterReadingState.cpp
        src/tokenize/ConstantCompletedState.cpp
        src/tokenize/DigitCompleteState.cpp
        src/tokenize/DigitOrCharacterReadingCompletedState.cpp
        src/tokenize/DigitReadingState.cpp
        src/tokenize/EmptyOperatorParenthesisOpenState.cpp
        src/tokenize/EmptyState.cpp
        src/tokenize/FSM.cpp
        src/InvalidFormulaException.cpp
        src/tokenize/OperatorState.cpp
        src/tokenize/ParenthesisClosedState.cpp
        src/tokenize/ParenthesisOpenState.cpp
        src/tokenize/PostfixOperationState.cpp
        src/tokenize/State.cpp
        src/tokenize/Token.cpp
        src/tokenize/Transition.cpp
        src/tokenize/VarCompletedState.cpp)

target_link_libraries(${project_name}-lib
        PUBLIC doctest::doctest
        )

target_include_directories(${project_name}-lib PUBLIC src)

## main binary

add_executable(${project_name}-bin
        src/main.cpp
        )

target_link_libraries(${project_name}-bin ${project_name}-lib)
add_dependencies(${project_name}-bin ${project_name}-lib)

## test binary

add_executable(${project_name}-test
        test/test.cpp
        )

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

# general properties

set_target_properties(${project_name}-lib ${project_name}-bin ${project_name}-test PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        )

enable_testing()
add_test(project-tests ${project_name}-test)

install(TARGETS ${project_name}-bin DESTINATION bin)
install(TARGETS ${project_name}-lib DESTINATION lib)
file(GLOB ROOT_HEADER_FILES "src/FunctionParser.hpp" "src/InvalidFormulaException.hpp")
file(GLOB TOKENIZE_HEADER_FILES "src/tokenize/Token.hpp")
file(GLOB AST_HEADER_FILES "src/ast/*.hpp")
install(FILES ${ROOT_HEADER_FILES} DESTINATION include/mathparser)
install(FILES ${TOKENIZE_HEADER_FILES} DESTINATION include/mathparser/tokenize)
install(FILES ${AST_HEADER_FILES} DESTINATION include/mathparser/ast)