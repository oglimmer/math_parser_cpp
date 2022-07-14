#pragma once

#include <vector>
#include <string>
#include <memory>

#include "characterType.hpp"
#include "ast/ASTBuilder.hpp"
#include "ast/ASTNode.hpp"


class LexicalAnalyzer {

public:
    std::unique_ptr<std::vector<std::shared_ptr<Token>>> parseToTokens(const std::string &input) const;

};

