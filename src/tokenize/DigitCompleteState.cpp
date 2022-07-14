
#include "DigitCompleteState.hpp"

DigitCompleteState::DigitCompleteState(const std::string &number) : number(number) {}

std::shared_ptr<Token> DigitCompleteState::getToken() const {
    return std::make_unique<Token>(number, TokenType::NUMBER);
}


