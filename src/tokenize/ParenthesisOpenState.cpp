
#include "ParenthesisOpenState.hpp"

#include <string>

ParenthesisOpenState::ParenthesisOpenState(char character) : character(character) {}

std::shared_ptr<Token> ParenthesisOpenState::getToken() const {
    return std::make_unique<Token>(std::string(1, character), TokenType::PARENTHESIS_OPEN);
}