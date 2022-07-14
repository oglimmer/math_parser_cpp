
#pragma once

#include "DigitOrCharacterReadingCompletedState.hpp"
#include "Token.hpp"
#include <string>


class DigitCompleteState : public DigitOrCharacterReadingCompletedState {
private:
    std::string number;
public:
    DigitCompleteState(const std::string &number);

    std::shared_ptr<Token> getToken() const;

};


