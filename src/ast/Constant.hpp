
#pragma once

#include "Expression.hpp"


class ConstantEnum {
private:
    std::string name;
    long double val;

    static ConstantEnum PI;
    static ConstantEnum E;
    static ConstantEnum ALL[];

    ConstantEnum(const std::string &name, long double val);

public:

    const std::string &getName() const;

    long double getValue() const;

    static ConstantEnum &byName(const std::string &name);

    static bool match(const std::string &name);
};

class Constant : public Expression, public std::enable_shared_from_this<Constant> {
private:
    ConstantEnum constantImpl;
public:
    Constant(const std::string &constantName);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve(std::map<std::string, long double> vars) const;

    std::shared_ptr<Expression> simplify();

    bool openForInput() const;

    std::string toString() const;
};