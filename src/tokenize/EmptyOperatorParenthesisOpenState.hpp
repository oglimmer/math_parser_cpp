
#pragma once

#include "State.hpp"
#include "Transition.hpp"
#include <memory>


class EmptyOperatorParenthesisOpenState : public State {
public:
    void validate(char readCharacter, char nextCharacter) const;

    std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
};

