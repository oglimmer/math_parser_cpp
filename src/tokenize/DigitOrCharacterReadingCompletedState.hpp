
#pragma once

#include "State.hpp"
#include "Transition.hpp"


#include <string>


class DigitOrCharacterReadingCompletedState : public State {
public:
    void validate(char readCharacter, char nextCharacter) const;

    std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
};


