#pragma once

#include "ASTBuilder.hpp"
#include "Operation.hpp"

class BinaryOperationExpression : public Expression, public std::enable_shared_from_this<BinaryOperationExpression> {
private:
    std::shared_ptr<Expression> op1;
    std::shared_ptr<Expression> op2;
    std::shared_ptr<Operation> op;
public:
    BinaryOperationExpression(std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op);

    BinaryOperationExpression(std::shared_ptr<Expression> op1, std::shared_ptr<Operation> op,
                              std::shared_ptr<Expression> op2);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve(std::map<std::string, long double> vars) const;

    std::shared_ptr<Expression> simplify();

    void validate() const;

    bool openForInput() const;

    std::string toString() const;
};

