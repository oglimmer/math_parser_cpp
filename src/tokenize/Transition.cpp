
#include "Transition.hpp"


Transition::Transition(std::shared_ptr<State> targetState, std::shared_ptr<Token> token)
        : token(token), targetState(targetState) {

}

std::shared_ptr<State> Transition::getTargetState() const {
    return targetState;
}

std::shared_ptr<Token> Transition::getToken() const {
    return token;
}


