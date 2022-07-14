
#include "CharacterReadingState.hpp"
#include "InvalidFormulaException.hpp"
#include "VarCompletedState.hpp"
#include "PostfixOperationState.hpp"
#include "ConstantCompletedState.hpp"
#include "characterType.hpp"
#include "ast/Parenthesis.hpp"


CharacterReadingState::CharacterReadingState(char initialDigit) {
    numberBuffer << initialDigit;
}

void CharacterReadingState::validate(char readCharacter, char nextCharacter) const {
    if (!isAlphabetic(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> CharacterReadingState::transition(char readCharacter, char nextCharacter) {
    numberBuffer << readCharacter;

    if (nextCharacter == 0 || isOperator(nextCharacter) ||
        nextCharacter == PARENTHESIS_CHAR_CLOSE ||
        (nextCharacter == PARENTHESIS_CHAR_OPEN && containsKeyword(numberBuffer.str()))) {
        if (containsConstant(numberBuffer.str())) {
            return std::make_shared<ConstantCompletedState>(numberBuffer.str())->getTransition();
        } else if (containsKeyword(numberBuffer.str())) {
            return std::make_shared<PostfixOperationState>(numberBuffer.str())->getTransition();
        } else {
            return std::make_shared<VarCompletedState>(numberBuffer.str())->getTransition();
        }
    }

    return getTransition();
}

std::shared_ptr<Token> CharacterReadingState::getToken() const {
    return nullptr;
}

