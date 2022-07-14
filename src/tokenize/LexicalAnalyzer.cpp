#include "LexicalAnalyzer.hpp"


#include "FSM.hpp"

#include <memory>

std::unique_ptr<std::vector<std::shared_ptr<Token>>> LexicalAnalyzer::parseToTokens(const std::string &input) const {
    auto resultVector = std::make_unique<std::vector<std::shared_ptr<Token>>>();
    FSM fsm;
    for (auto pos = 0; pos < input.length(); pos++) {

        char readCharacter = input[pos];
        char nextCharacter = input[pos + 1];

        std::shared_ptr<Token> token = fsm.transition(readCharacter, nextCharacter);
        if (token) {
            resultVector->push_back(token);
        }

    }
    return resultVector;
}
