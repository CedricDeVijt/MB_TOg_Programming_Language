#include "AST.h"

Statement::Statement(NodeType kind)
: kind(kind) {}

NodeType Statement::getKind() const {
    return kind;
}

Program::Program(const std::list <Statement> &body)
: Statement(NodeType::Program), body(body) {}

const std::list<Statement> &Program::getBody() const {
    return body;
}

Expression::Expression(NodeType kind)
: Statement(kind) {}

BinaryExpression::BinaryExpression(const Statement &left, const Statement &right, const std::string &op)
: Expression(NodeType::BinaryExpression), left(left), right(right), op(op) {}

const Statement &BinaryExpression::getLeft() const {
    return left;
}

const Statement &BinaryExpression::getRight() const {
    return right;
}

const std::string &BinaryExpression::getOp() const {
    return op;
}

Identifier::Identifier(const std::string &symbol) : Expression(NodeType::Identifier), symbol(symbol) {}

const std::string &Identifier::getSymbol() const {
    return symbol;
}

Float::Float(float value) : Expression(NodeType::Float), value(value) {}

float Float::getValue() const {
    return value;
}

String::String(const std::string &value) : Expression(NodeType::String), value(value) {}

const std::string &String::getValue() const {
    return value;
}

Bool::Bool(bool value) : Expression(NodeType::Bool), value(value) {}

bool Bool::isValue() const {
    return value;
}

FunctionDeclaration::FunctionDeclaration(const std::string &name, const std::list<Identifier> &parameters, const std::list<Statement> &body)
: Statement(NodeType::FunctionDeclaration), name(name), parameters(parameters), body(body) {}

const std::string &FunctionDeclaration::getName() const {
    return name;
}

const std::list<Identifier> &FunctionDeclaration::getParameters() const {
    return parameters;
}

const std::list<Statement> &FunctionDeclaration::getBody() const {
    return body;
}

FunctionCall::FunctionCall(const std::string &name, const std::list <Expression> &parameters)
: Expression(NodeType::FunctionCall), name(name), parameters(parameters) {}

const std::string &FunctionCall::getName() const {
    return name;
}

const std::list<Expression> &FunctionCall::getParameters() const {
    return parameters;
}

IfStatement::IfStatement(const Expression &condition, const std::list <Statement> &thenBody, const std::list <Statement> &elseBody)
: Statement(NodeType::IfStatement), condition(condition), thenBody(thenBody), elseBody(elseBody) {}

const Expression &IfStatement::getCondition() const {
    return condition;
}

const std::list<Statement> &IfStatement::getThenBody() const {
    return thenBody;
}

const std::list<Statement> &IfStatement::getElseBody() const {
    return elseBody;
}

AssignmentStatement::AssignmentStatement(const Identifier &variable, const Expression &value)
: Statement(NodeType::AssignmentStatement), variable(variable), value(value) {}

const Identifier &AssignmentStatement::getVariable() const {
    return variable;
}

const Expression &AssignmentStatement::getValue() const {
    return value;
}

WhileStatement::WhileStatement(const Expression &condition, const std::list <Statement> &body)
: Statement(NodeType::WhileStatement), condition(condition), body(body) {}

const Expression &WhileStatement::getCondition() const {
    return condition;
}

const std::list<Statement> &WhileStatement::getBody() const {
    return body;
}

