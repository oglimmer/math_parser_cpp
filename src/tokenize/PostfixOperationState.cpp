
#include <string>
#include "PostfixOperationState.hpp"


PostfixOperationState::PostfixOperationState(const std::string &operatorName) : operatorName(operatorName) {}

std::shared_ptr<Token> PostfixOperationState::getToken() const {
    return std::make_unique<Token>(operatorName, TokenType::POSTFIX_OPERATOR);
}