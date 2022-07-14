
#include "DigitOrCharacterReadingCompletedState.hpp"
#include "ast/Parenthesis.hpp"
#include "characterType.hpp"
#include "InvalidFormulaException.hpp"
#include "OperatorState.hpp"
#include "ParenthesisClosedState.hpp"


void DigitOrCharacterReadingCompletedState::validate(char readCharacter, char nextCharacter) const {
    if (!isOperator(readCharacter) && readCharacter != PARENTHESIS_CHAR_CLOSE) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> DigitOrCharacterReadingCompletedState::transition(char readCharacter, char nextCharacter) {
    if (isOperator(readCharacter)) {
        return std::make_shared<OperatorState>(readCharacter)->getTransition();
    } else if (readCharacter == PARENTHESIS_CHAR_CLOSE) {
        return std::make_shared<ParenthesisClosedState>(readCharacter)->getTransition();
    }
    return nullptr;
}