#pragma once

#include <string>

class ASTNode {
public:
    virtual bool openForInput() const = 0;

    virtual std::string toString() const = 0;
};
