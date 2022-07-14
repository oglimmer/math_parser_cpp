#pragma once

#include <memory>
#include <map>
#include "LexicalAnalyzer.hpp"

class Token;

class Operation;

class ASTNode {
public:
    virtual bool openForInput() const = 0;

    virtual std::string toString() const = 0;
};

class Expression : public ASTNode {
public:
    virtual std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd) = 0;

    virtual long double resolve(std::map<std::string, long double> vars) const = 0;

    virtual std::shared_ptr<Expression> simplify() = 0;

    virtual void validate() const {

    }
};

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

class Number : public Expression, public std::enable_shared_from_this<Number> {
private:
    long double val;
public:
    Number(long double val);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve(std::map<std::string, long double> vars) const;

    std::shared_ptr<Expression> simplify();

    bool openForInput() const;

    std::string toString() const;
};

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

class Variable : public Expression, public std::enable_shared_from_this<Variable> {
private:
    std::string variableName;
public:
    Variable(const std::string &variableName);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve(std::map<std::string, long double> vars) const;

    std::shared_ptr<Expression> simplify();

    bool openForInput() const;

    std::string toString() const;
};

#define PARENTHESIS_CHAR_OPEN '('
#define PARENTHESIS_CHAR_CLOSE ')'

class Parenthesis : public Expression, public std::enable_shared_from_this<Parenthesis> {
private:
    std::shared_ptr<Expression> nestedExp;
    bool closed;
    char c;
public:
    Parenthesis(char c);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve(std::map<std::string, long double> vars) const;

    std::shared_ptr<Expression> simplify();

    bool openForInput() const;

    void validate() const;

    std::string toString() const;
};

class Operation : public ASTNode {
private:
    char symbol;
    int precedence;
public:
    Operation(char symbol);

    int getPrecedence() const;

    long double resolve(std::map<std::string, long double> vars, std::shared_ptr<Expression> op1,
                        std::shared_ptr<Expression> op2) const;

    bool openForInput() const;

    std::string toString() const;

    static bool match(char symbol);
};

typedef long double (*FuncPtrToTrigonometry)(long double);

class PostfixOperationEnum {
private:
    std::string name;
    FuncPtrToTrigonometry functionPointer;

    static PostfixOperationEnum SIN;
    static PostfixOperationEnum COS;
    static PostfixOperationEnum TAN;
    static PostfixOperationEnum ASIN;
    static PostfixOperationEnum ACOS;
    static PostfixOperationEnum ATAN;
    static PostfixOperationEnum SQRT;
    static PostfixOperationEnum LOG;
    static PostfixOperationEnum LOGTEN;
    static PostfixOperationEnum ALL[];

    PostfixOperationEnum(const std::string &name, FuncPtrToTrigonometry functionPointer)
            : name(name), functionPointer(functionPointer) {
    }
public:

    const std::string &getName() const;

    FuncPtrToTrigonometry getFuncPtrOne() const;

    static PostfixOperationEnum &byName(const std::string &name);

    static bool match(const std::string &name);
};

class PostfixOperation : public Expression, public std::enable_shared_from_this<PostfixOperation> {
private:
    std::shared_ptr<Expression> nestedExp;
    PostfixOperationEnum postfixOperationImpl;
public:
    PostfixOperation(const std::string &operatorName);

    std::shared_ptr<Expression> add(std::shared_ptr<ASTNode> toAdd);

    long double resolve(std::map<std::string, long double> vars) const;

    std::shared_ptr<Expression> simplify();

    bool openForInput() const;

    void validate() const;

    std::string toString() const;
};

class ASTBuilder {
public:
    std::shared_ptr<Expression> tokensToExpression(const std::vector<std::shared_ptr<Token>> &tokens) const;


};
