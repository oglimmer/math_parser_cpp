
#include "FSM.hpp"
#include "EmptyState.hpp"


FSM::FSM() : state(std::make_shared<EmptyState>()) {

}

std::shared_ptr<Token> FSM::transition(char readCharacter, char nextCharacter) {
    state->validate(readCharacter, nextCharacter);
    auto transition = state->transition(readCharacter, nextCharacter);
    state = transition->getTargetState();
    return transition->getToken();
}


