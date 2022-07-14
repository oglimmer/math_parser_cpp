
#pragma once

#include "DigitOrCharacterReadingCompletedState.hpp"


class VarCompletedState : public DigitOrCharacterReadingCompletedState {
private:
    std::string varName;
public:
    VarCompletedState(const std::string &varName);

    std::shared_ptr<Token> getToken() const;

};


