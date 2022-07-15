
#pragma once


#include <string>
#include "EmptyOperatorParenthesisOpenState.hpp"
#include "Token.hpp"

class PostfixOperationState : public EmptyOperatorParenthesisOpenState {
private:
    std::string operatorName;
public:
    PostfixOperationState(const std::string &operatorName);

    std::shared_ptr<Token> getToken() const override;

};
