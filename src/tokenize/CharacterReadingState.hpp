
#pragma once

#include "State.hpp"
#include "Transition.hpp"
#include "Token.hpp"
#include <sstream>


class CharacterReadingState : public State {
private:
    std::stringstream numberBuffer;
public:
    CharacterReadingState(char initialDigit);

    void validate(char readCharacter, char nextCharacter) const override;

    std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) override;

    std::shared_ptr<Token> getToken() const override;

};

