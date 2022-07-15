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

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) override;

    long double resolve(std::map<std::string, long double> vars) const override;

    std::shared_ptr<Expression> simplify() override;

    void validate() const override;

    bool openForInput() const override;

    std::string toString() const override;
};

