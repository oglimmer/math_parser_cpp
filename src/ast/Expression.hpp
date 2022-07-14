#pragma once

#include <memory>
#include <map>
#include "ASTNode.hpp"


class Expression : public ASTNode {
public:
    virtual std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) = 0;

    virtual long double resolve(std::map<std::string, long double> vars) const = 0;

    virtual std::shared_ptr<Expression> simplify() = 0;

    virtual void validate() const {

    }
};

