
#pragma once

#include "EmptyOperatorParenthesisOpenState.hpp"
#include "Token.hpp"

class EmptyState : public EmptyOperatorParenthesisOpenState {
public:
    std::shared_ptr<Token> getToken() const;
};
