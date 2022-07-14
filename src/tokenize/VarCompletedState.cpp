
#include "VarCompletedState.hpp"

VarCompletedState::VarCompletedState(const std::string &varName) : varName(varName) {}

std::shared_ptr<Token> VarCompletedState::getToken() const {
    return std::make_unique<Token>(varName, TokenType::VARIABLE);
}