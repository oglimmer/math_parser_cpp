#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "characterType.hpp"
#include "ASTBuilder.hpp"

enum TokenType {
    NUMBER, OPERATOR, PARENTHESIS_OPENED, PARENTHESIS_CLOSE
};

class ASTNode;

class Token {
private:
    std::string data;
    TokenType tokenType;
public:
    Token(const std::string &data, TokenType tokenType);

    const std::string &getData();

    std::shared_ptr<ASTNode> toASTNode();
};

class InvalidFormulaException : public std::exception {
private:
    std::string message_;
public:
    explicit InvalidFormulaException(const std::string &message);

    const char *what() const noexcept override {
        return message_.c_str();
    }
};

class State;

class Transition {
    private:
        std::shared_ptr<State> targetState;
        std::shared_ptr<Token> token;
    public:
        Transition(std::shared_ptr<State> targetState, std::shared_ptr<Token> token);
        std::shared_ptr<State> getTargetState();
        std::shared_ptr<Token> getToken();
};


class State : public std::enable_shared_from_this<State> {

    public:
        virtual void validate(char readCharacter, char nextCharacter) = 0;

        virtual std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter) = 0;

        virtual std::shared_ptr<Token> getToken() = 0;

        std::shared_ptr<Transition> getTransition();
};

class DigitOrCharacterReadingCompletedState : public State {
public:
    void validate(char readCharacter, char nextCharacter);

    std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
};

class EmptyOperatorParenthesisOpenState : public State {
public:
    void validate(char readCharacter, char nextCharacter);

    std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);
};

class DigitReadingState : public State {
    private:
        std::stringstream numberBuffer;
    public:
        DigitReadingState(char initialDigit);

        void validate(char readCharacter, char nextCharacter);

        std::shared_ptr<Transition> transition(char readCharacter, char nextCharacter);

        std::shared_ptr<Token> getToken();

};

class ParenthesisOpenState : public EmptyOperatorParenthesisOpenState {
private:
    char character;
public:
    ParenthesisOpenState(char character);

    std::shared_ptr<Token> getToken();

};

class ParenthesisClosedState : public DigitOrCharacterReadingCompletedState {
private:
    char character;
public:
    ParenthesisClosedState(char character);

    std::shared_ptr<Token> getToken();

};

class DigitCompleteState : public DigitOrCharacterReadingCompletedState {
    private:
        std::string number;
    public:
        DigitCompleteState(const std::string& number);

        std::shared_ptr<Token> getToken();

};

class OperatorState : public EmptyOperatorParenthesisOpenState {
    private:
        char symbol;
    public:
        OperatorState(char symbol);

        std::shared_ptr<Token> getToken();

};

class EmptyState : public EmptyOperatorParenthesisOpenState {
    public:
        std::shared_ptr<Token> getToken();
};



class FSM {
    private:
        std::shared_ptr<State> state;
    public:
        FSM();
        std::shared_ptr<Token> transition(char readCharacter, char nextCharacter);
};

class LexicalAnalyzer {

public:
    std::unique_ptr<std::vector<std::shared_ptr<Token>>> parseToTokens(const std::string &input);

};

