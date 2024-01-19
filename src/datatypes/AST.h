#ifndef MB_TOG_PROGRAMMING_LANGUAGE_AST_H
#define MB_TOG_PROGRAMMING_LANGUAGE_AST_H

#include <list>
#include <string>

enum class NodeType {
    Program,
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

    NodeType getKind() const;

private:
    NodeType kind;
};

class Program : public Statement {
public:
    Program(const std::list<Statement> &body);

    void push_back(const Statement& statement);

    const std::list<Statement> &getBody() const;

private:
    std::list<Statement> body;
};

class Expression : public Statement {
public:
    Expression(NodeType kind);
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(const Statement &left, const Statement &right, const std::string &op);

    const Statement &getLeft() const;

    const Statement &getRight() const;

    const std::string &getOp() const;

private:
    Statement left;
    Statement right;
    std::string op;
};

class Identifier : public Expression {
public:
    Identifier(const std::string &symbol);

    const std::string &getSymbol() const;

private:
    std::string symbol;
};

class Float : public Expression {
public:
    Float(float value);

    float getValue() const;

private:
    float value;
};

class String : public Expression {
public:
    String(const std::string &value);

    const std::string &getValue() const;

private:
    std::string value;
};

class Bool : public Expression {
public:
    Bool(bool value);

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
    FunctionCall(const std::string &name, const std::list<Expression> &parameters);

    const std::string &getName() const;

    const std::list<Expression> &getParameters() const;

private:
    std::string name;
    std::list<Expression> parameters;
};

class IfStatement : public Statement {
public:
    IfStatement(const Expression& condition, const std::list<Statement>& thenBody, const std::list<Statement>& elseBody = {});

    const Expression &getCondition() const;

    const std::list<Statement> &getThenBody() const;

    const std::list<Statement> &getElseBody() const;

private:
    Expression condition;
    std::list<Statement> thenBody;
    std::list<Statement> elseBody;
};

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(const Identifier& variable, const Expression& value);

    const Identifier &getVariable() const;

    const Expression &getValue() const;

private:
    Identifier variable;
    Expression value;
};

class WhileStatement : public Statement {
public:
    WhileStatement(const Expression& condition, const std::list<Statement>& body);

    const Expression &getCondition() const;

    const std::list<Statement> &getBody() const;

private:
    Expression condition;
    std::list<Statement> body;
};

#endif //MB_TOG_PROGRAMMING_LANGUAGE_AST_H
