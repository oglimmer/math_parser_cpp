
#include "OperatorState.hpp"

#include <string>

OperatorState::OperatorState(char symbol) : symbol(symbol) {}

std::shared_ptr<Token> OperatorState::getToken() const {
    return std::make_unique<Token>(std::string(1, symbol), TokenType::OPERATOR);
}