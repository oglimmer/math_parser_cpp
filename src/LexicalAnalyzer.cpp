#include "LexicalAnalyzer.hpp"

#include <iostream>
#include <memory>


Token::Token(const std::string &data, TokenType tokenType) : data(data), tokenType(tokenType) {}

const std::string &Token::getData() {
    return data;
}

std::shared_ptr<ASTNode> Token::toASTNode() {
    switch (tokenType) {
        case TokenType::NUMBER:
            return std::shared_ptr<Number>(new Number(std::stold(data)));
        case TokenType::OPERATOR:
            return std::make_shared<Operation>(data[0]);
        case TokenType::PARENTHESIS_OPENED:
        case TokenType::PARENTHESIS_CLOSE:
            return std::make_shared<Parenthesis>(data[0]);
        case TokenType::CONSTANT:
            return std::make_shared<Constant>(data);
        case TokenType::VARIABLE:
            return std::make_shared<Variable>(data);
        case TokenType::POSTFIX_OPERATOR:
            return std::make_shared<PostfixOperation>(data);
    }
    return nullptr;
}

std::string Token::toString() const {
    std::string typeStr;
    switch (tokenType) {
        case TokenType::NUMBER:
            typeStr = "NUMBER";
            break;
        case TokenType::OPERATOR:
            typeStr = "OPERATOR";
            break;
        case TokenType::PARENTHESIS_OPENED:
            typeStr = "PARENTHESIS_OPENED";
            break;
        case TokenType::PARENTHESIS_CLOSE:
            typeStr = "PARENTHESIS_CLOSE";
            break;
        case TokenType::CONSTANT:
            typeStr = "CONSTANT";
            break;
        case TokenType::VARIABLE:
            typeStr = "VARIABLE";
            break;
        case TokenType::POSTFIX_OPERATOR:
            typeStr = "POSTFIX_OPERATOR";
            break;
    }
    return "{type:" + typeStr + ", data:" + data + "}";
}

/* *************************************************************************************************** */

InvalidFormulaException::InvalidFormulaException(const std::string &message) : message_(message) {
}

/* *************************************************************************************************** */

Transition::Transition(std::shared_ptr<State> targetState, std::shared_ptr<Token> token) : token(token),
                                                                                           targetState(targetState) {}

std::shared_ptr<State> Transition::getTargetState() {
    return targetState;
}

std::shared_ptr<Token> Transition::getToken() {
    return token;
}

/* *************************************************************************************************** */

std::shared_ptr<Transition> State::getTransition() {
    return std::make_shared<Transition>(shared_from_this(), getToken());
}

/* *************************************************************************************************** */


void DigitOrCharacterReadingCompletedState::validate(char readCharacter, char nextCharacter) {
    if (!isOperator(readCharacter) && readCharacter != PARENTHESIS_CLOSED) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> DigitOrCharacterReadingCompletedState::transition(char readCharacter, char nextCharacter) {
    if (isOperator(readCharacter)) {
        return std::make_shared<OperatorState>(readCharacter)->getTransition();
    } else if (readCharacter == PARENTHESIS_CLOSED) {
        return std::make_shared<ParenthesisClosedState>(readCharacter)->getTransition();
    }
    return nullptr;
}

/* *************************************************************************************************** */


void EmptyOperatorParenthesisOpenState::validate(char readCharacter, char nextCharacter) {
    if (isOperator(readCharacter) && !isAlgebraicSign(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
    if (readCharacter == PARENTHESIS_CLOSED) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
    if (!isNumber(readCharacter) && !isAlgebraicSign(readCharacter) && readCharacter != PARENTHESIS_OPEN && !isAlphabetic(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> EmptyOperatorParenthesisOpenState::transition(char readCharacter, char nextCharacter) {
    if (readCharacter == PARENTHESIS_OPEN) {
        return std::make_shared<ParenthesisOpenState>(readCharacter)->getTransition();
    } else if (isNumber(nextCharacter)) {
        return std::make_shared<DigitReadingState>(readCharacter)->getTransition();
    } else if (isAlphabetic(nextCharacter)) {
        return std::make_shared<CharacterReadingState>(readCharacter)->getTransition();
    } else if (nextCharacter == 0 || isOperator(nextCharacter) || nextCharacter == PARENTHESIS_CLOSED) {
        if (isNumber(readCharacter)) {
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

/* *************************************************************************************************** */

DigitReadingState::DigitReadingState(char initialDigit) {
    numberBuffer << initialDigit;
}

void DigitReadingState::validate(char readCharacter, char nextCharacter) {
    if (isOperator(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> DigitReadingState::transition(char readCharacter, char nextCharacter) {
    numberBuffer << readCharacter;

    if (isOperator(nextCharacter) || nextCharacter == 0 || nextCharacter == PARENTHESIS_CLOSED) {
        return std::make_shared<DigitCompleteState>(numberBuffer.str())->getTransition();
    }

    return getTransition();
}

std::shared_ptr<Token> DigitReadingState::getToken() {
    return nullptr;
}

/* *************************************************************************************************** */

CharacterReadingState::CharacterReadingState(char initialDigit) {
    numberBuffer << initialDigit;
}

void CharacterReadingState::validate(char readCharacter, char nextCharacter) {
    if (!isAlphabetic(readCharacter)) {
        throw InvalidFormulaException("Invalid character found " + std::string(1, readCharacter));
    }
}

std::shared_ptr<Transition> CharacterReadingState::transition(char readCharacter, char nextCharacter) {
    numberBuffer << readCharacter;

    if (nextCharacter == 0 || isOperator(nextCharacter) ||
            nextCharacter == PARENTHESIS_CLOSED ||
            (nextCharacter == PARENTHESIS_OPEN && containsKeyword(numberBuffer.str()))) {
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

std::shared_ptr<Token> CharacterReadingState::getToken() {
    return nullptr;
}

/* *************************************************************************************************** */

ParenthesisOpenState::ParenthesisOpenState(char character) : character(character) {}

std::shared_ptr<Token> ParenthesisOpenState::getToken() {
    return std::make_unique<Token>(std::string(1, character), TokenType::PARENTHESIS_OPENED);
}

/* *************************************************************************************************** */

ParenthesisClosedState::ParenthesisClosedState(char character) : character(character) {}

std::shared_ptr<Token> ParenthesisClosedState::getToken() {
    return std::make_unique<Token>(std::string(1, character), TokenType::PARENTHESIS_CLOSE);
}

/* *************************************************************************************************** */

DigitCompleteState::DigitCompleteState(const std::string &number) : number(number) {}

std::shared_ptr<Token> DigitCompleteState::getToken() {
    return std::make_unique<Token>(number, TokenType::NUMBER);
}
/* *************************************************************************************************** */

ConstantCompletedState::ConstantCompletedState(const std::string &constant) : constant(constant) {}

std::shared_ptr<Token> ConstantCompletedState::getToken() {
    return std::make_unique<Token>(constant, TokenType::CONSTANT);
}

/* *************************************************************************************************** */

VarCompletedState::VarCompletedState(const std::string &varName) : varName(varName) {}

std::shared_ptr<Token> VarCompletedState::getToken() {
    return std::make_unique<Token>(varName, TokenType::VARIABLE);
}

/* *************************************************************************************************** */

OperatorState::OperatorState(char symbol) : symbol(symbol) {}

std::shared_ptr<Token> OperatorState::getToken() {
    return std::make_unique<Token>(std::string(1, symbol), TokenType::OPERATOR);
}

/* *************************************************************************************************** */

PostfixOperationState::PostfixOperationState(const std::string& operatorName) : operatorName(operatorName) {}

std::shared_ptr<Token> PostfixOperationState::getToken() {
    return std::make_unique<Token>(operatorName, TokenType::POSTFIX_OPERATOR);
}

/* *************************************************************************************************** */

std::shared_ptr<Token> EmptyState::getToken() {
    return nullptr;
}

/* *************************************************************************************************** */

FSM::FSM() : state(std::make_shared<EmptyState>()) {

}

/* *************************************************************************************************** */

std::shared_ptr<Token> FSM::transition(char readCharacter, char nextCharacter) {
    state->validate(readCharacter, nextCharacter);
    auto transition = state->transition(readCharacter, nextCharacter);
    state = transition->getTargetState();
    return transition->getToken();
}

/* *************************************************************************************************** */

std::unique_ptr<std::vector<std::shared_ptr<Token>>> LexicalAnalyzer::parseToTokens(const std::string &input) {
    auto resultVector = std::make_unique<std::vector<std::shared_ptr<Token>>>();
    FSM fsm;
    for (auto i = 0; i < input.length(); i++) {

        char readCharacter = input[i];
        char nextCharacter = input[i + 1];

        auto token = fsm.transition(readCharacter, nextCharacter);
        if (token) {
            resultVector->push_back(token);
        }

    }
    return resultVector;
}
