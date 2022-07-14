
#pragma once

#include "State.hpp"
#include <memory>

class State;

class Token;

class Transition {
private:
    std::shared_ptr<State> targetState;
    std::shared_ptr<Token> token;
public:
    Transition(std::shared_ptr<State> targetState, std::shared_ptr<Token> token);

    std::shared_ptr<State> getTargetState() const;

    std::shared_ptr<Token> getToken() const;
};


