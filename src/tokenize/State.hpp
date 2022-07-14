
#pragma once


#include <memory>
#include "Transition.hpp"
#include "Token.hpp"

class Transition;

class Token;

class State : public std::enable_shared_from_this<State> {

public:
    virtual void validate(char readCharacter, char nextCharacter) const = 0;

    virtual std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) = 0;

    virtual std::shared_ptr<Token> getToken() const = 0;

    std::shared_ptr<Transition> getTransition();
};

