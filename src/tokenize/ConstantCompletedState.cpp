
#include "ConstantCompletedState.hpp"
#include "Token.hpp"


ConstantCompletedState::ConstantCompletedState(const std::string &constant) : constant(constant) {}

std::shared_ptr<Token> ConstantCompletedState::getToken() const {
    return std::make_unique<Token>(constant, TokenType::CONSTANT);
}