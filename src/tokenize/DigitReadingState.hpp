
#pragma once

#include "State.hpp"
#include "Transition.hpp"
#include "Token.hpp"
#include <sstream>


class DigitReadingState : public State {
private:
    std::stringstream numberBuffer;
public:
    DigitReadingState(char initialDigit);

    void validate(char readCharacter, char nextCharacter) const;

    std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);

    std::shared_ptr<Token> getToken() const;

};

