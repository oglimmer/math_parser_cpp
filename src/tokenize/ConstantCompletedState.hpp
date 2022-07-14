
#pragma once

#include "DigitOrCharacterReadingCompletedState.hpp"
#include <string>

class ConstantCompletedState : public DigitOrCharacterReadingCompletedState {
private:
    std::string constant;
public:
    ConstantCompletedState(const std::string &constant);

    std::shared_ptr<Token> getToken() const;

};
