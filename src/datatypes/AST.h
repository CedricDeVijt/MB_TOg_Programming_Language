#ifndef MB_TOG_PROGRAMMING_LANGUAGE_AST_H
#define MB_TOG_PROGRAMMING_LANGUAGE_AST_H

#include <list>
#include <string>
#include <memory>
#include <vector>
#include "../modules/executionEnvironment/Environment.h"

enum class NodeType {
    Program,
    Integer,
    Float,
    String,
    Bool,
    Identifier,
    BinaryExpression,
    FunctionCall,
    FunctionDeclaration,
    IfStatement,
    AssignmentStatement,
    WhileStatement
};

class Statement {
public:
    Statement(NodeType kind);

    virtual ~Statement() = default;

    NodeType getKind() const;

private:
    NodeType kind;
};

class Program : public Statement {
public:
    Program(std::list<std::unique_ptr<Statement>>&& body);

    const std::list<std::unique_ptr<Statement>>& getBody() const;

private:
    std::list<std::unique_ptr<Statement>> body;
};

class Expression : public Statement {
public:
    Expression(NodeType kind);

    virtual ~Expression() = default;
    virtual Value evaluate(Env& env) const = 0; // Pure virtual function
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::unique_ptr<Statement> left, std::unique_ptr<Statement> right, std::string op);

    Value evaluate(Env& env) const override;

    const Statement* getLeft() const;

    const Statement* getRight() const;

    const std::string &getOp() const;

private:
    std::unique_ptr<Statement> left;
    std::unique_ptr<Statement> right;
    std::string op;
};

class Identifier : public Expression {
public:
    Identifier(const std::string &symbol);

    Value evaluate(Env& env) const override;

    const std::string &getSymbol() const;

private:
    std::string symbol;
};

class Integer : public Expression {
public:
    Integer(int value);

    Value evaluate(Env& env) const override;

    int getValue() const;

private:
    int value;
};

class Float : public Expression {
public:
    Float(float value);

    Value evaluate(Env& env) const override;

    float getValue() const;

private:
    float value;
};

class String : public Expression {
public:
    String(const std::string &value);

    Value evaluate(Env& env) const override;

    const std::string &getValue() const;

private:
    std::string value;
};

class Bool : public Expression {
public:
    Bool(bool value);

    Value evaluate(Env& env) const override;

    bool isValue() const;

private:
    bool value;
};

class FunctionDeclaration : public Statement {
public:
    FunctionDeclaration(const std::string& name, const std::list<Identifier>& parameters, const std::list<Statement>& body);

    const std::string &getName() const;

    const std::list<Identifier> &getParameters() const;

    const std::list<Statement> &getBody() const;

private:
    std::string name;
    std::list<Identifier> parameters;
    std::list<Statement> body;
};

class FunctionCall : public Expression {
public:
    FunctionCall(const std::string &name, std::list<std::unique_ptr<Expression>>&& parameters);

    Value evaluate(Env& env) const override;

    const std::string &getName() const;

    const std::list<std::unique_ptr<Expression>>& getParameters() const;

private:
    std::string name;
    std::list<std::unique_ptr<Expression>> parameters;
};

class IfStatement : public Statement {
public:
    IfStatement(std::unique_ptr<Expression> condition, const std::list<Statement>& thenBody, const std::list<Statement>& elseBody = {});

    const Expression& getCondition() const;

    const std::list<Statement> &getThenBody() const;

    const std::list<Statement> &getElseBody() const;

private:
    std::unique_ptr<Expression> condition;
    std::list<Statement> thenBody;
    std::list<Statement> elseBody;
};

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(const Identifier id, std::unique_ptr<Expression> expr);

    const Identifier &getVariable() const;

    const Expression* getValue() const;

private:
    Identifier variable;
    std::unique_ptr<Expression> value;
};

class WhileStatement : public Statement {
public:
    WhileStatement(std::unique_ptr<Expression> condition, const std::list<Statement>& body);

    const Expression &getCondition() const;

    const std::list<Statement> &getBody() const;

private:
    std::unique_ptr<Expression> condition;
    std::list<Statement> body;
};

#endif //MB_TOG_PROGRAMMING_LANGUAGE_AST_H
