
#pragma once


#include <memory>
#include "State.hpp"
#include "Token.hpp"

class FSM {
private:
    std::shared_ptr<State> state;
public:
    FSM();

    std::shared_ptr<Token> transition(char readCharacter, char nextCharacter);
};