
#include "EmptyOperatorParenthesisOpenState.hpp"
#include "ast/Parenthesis.hpp"
#include "InvalidFormulaException.hpp"
#include "characterType.hpp"
#include "ParenthesisOpenState.hpp"
#include "DigitReadingState.hpp"
#include "CharacterReadingState.hpp"
#include "DigitCompleteState.hpp"
#include "ConstantCompletedState.hpp"
#include "PostfixOperationState.hpp"
#include "VarCompletedState.hpp"


void EmptyOperatorParenthesisOpenState::validate(char readCharacter, char nextCharacter) const {
    if (isOperator(readCharacter) && !isAlgebraicSign(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
    if (readCharacter == PARENTHESIS_CHAR_CLOSE) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
    if (!isDigit(readCharacter) && !isAlgebraicSign(readCharacter) && readCharacter != PARENTHESIS_CHAR_OPEN &&
        !isAlphabetic(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> EmptyOperatorParenthesisOpenState::transition(char readCharacter, char nextCharacter) {
    if (readCharacter == PARENTHESIS_CHAR_OPEN) {
        return std::make_shared<ParenthesisOpenState>(readCharacter)->getTransition();
    } else if (isDigit(nextCharacter)) {
        return std::make_shared<DigitReadingState>(readCharacter)->getTransition();
    } else if (isAlphabetic(nextCharacter)) {
        return std::make_shared<CharacterReadingState>(readCharacter)->getTransition();
    } else if (nextCharacter == 0 || isOperator(nextCharacter) || nextCharacter == PARENTHESIS_CHAR_CLOSE) {
        if (isDigit(readCharacter)) {
            return std::make_shared<DigitCompleteState>(std::string(1, readCharacter))->getTransition();
        } else if (isAlphabetic(readCharacter)) {
            if (containsConstant(std::string(1, readCharacter))) {
                return std::make_shared<ConstantCompletedState>(std::string(1, readCharacter))->getTransition();
            } else if (containsKeyword(std::string(1, readCharacter))) {
                return std::make_shared<PostfixOperationState>(std::string(1, readCharacter))->getTransition();
            } else {
                return std::make_shared<VarCompletedState>(std::string(1, readCharacter))->getTransition();
            }
        }
    }
    return getTransition();
}


