
#pragma once


#include <memory>
#include "EmptyOperatorParenthesisOpenState.hpp"
#include "Token.hpp"

class ParenthesisOpenState : public EmptyOperatorParenthesisOpenState {
private:
    char character;
public:
    ParenthesisOpenState(char character);

    std::shared_ptr<Token> getToken() const;

};

