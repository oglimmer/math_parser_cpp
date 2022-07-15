
#pragma once


#include <memory>
#include "EmptyOperatorParenthesisOpenState.hpp"
#include "Token.hpp"

class OperatorState : public EmptyOperatorParenthesisOpenState {
private:
    char symbol;
public:
    OperatorState(char symbol);

    std::shared_ptr<Token> getToken() const override;

};
