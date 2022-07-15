
#pragma once


#include <memory>
#include "DigitOrCharacterReadingCompletedState.hpp"
#include "Token.hpp"

class ParenthesisClosedState : public DigitOrCharacterReadingCompletedState {
private:
    char character;
public:
    ParenthesisClosedState(char character);

    std::shared_ptr<Token> getToken() const override;

};


