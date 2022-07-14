
#include "ParenthesisClosedState.hpp"

ParenthesisClosedState::ParenthesisClosedState(char character) : character(character) {}

std::shared_ptr<Token> ParenthesisClosedState::getToken() const {
    return std::make_unique<Token>(std::string(1, character), TokenType::PARENTHESIS_CLOSE);
}