
#include "DigitReadingState.hpp"
#include "DigitCompleteState.hpp"
#include "ast/Parenthesis.hpp"
#include "characterType.hpp"
#include "InvalidFormulaException.hpp"

DigitReadingState::DigitReadingState(char initialDigit) {
    numberBuffer << initialDigit;
}

void DigitReadingState::validate(char readCharacter, char nextCharacter) const {
    if (isOperator(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
    if (readCharacter == '.' && numberBuffer.str().find('.') != std::string::npos) {
        throw InvalidFormulaException("Invalid character, duplicate decimal separator.");
    }
}

std::shared_ptr<Transition> DigitReadingState::transition(char readCharacter, char nextCharacter) {
    numberBuffer << readCharacter;

    if (isOperator(nextCharacter) || nextCharacter == 0 || nextCharacter == PARENTHESIS_CHAR_CLOSE) {
        return std::make_shared<DigitCompleteState>(numberBuffer.str())->getTransition();
    }

    return getTransition();
}

std::shared_ptr<Token> DigitReadingState::getToken() const {
    return nullptr;
}

