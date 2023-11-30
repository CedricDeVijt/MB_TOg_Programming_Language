#include "AST.h"

Statement::Statement(NodeType kind)
: kind(kind) {}

Program::Program(const std::list <Statement> &body)
: Statement(NodeType::Program), body(body) {}

Expression::Expression(NodeType kind)
: Statement(kind) {}

BinaryExpression::BinaryExpression(const Statement &left, const Statement &right, const std::string &op)
: Expression(NodeType::BinaryExpression), left(left), right(right), op(op) {}

Identifier::Identifier(const std::string &symbol) : Expression(NodeType::Identifier), symbol(symbol) {}

Float::Float(float value) : Expression(NodeType::Float), value(value) {}

String::String(const std::string &value) : Expression(NodeType::String), value(value) {}

Bool::Bool(bool value) : Expression(NodeType::Bool), value(value) {}

FunctionDeclaration::FunctionDeclaration(const std::string &name, const std::list<Identifier> &parameters, const std::list<Statement> &body)
: Statement(NodeType::FunctionDeclaration), name(name), parameters(parameters), body(body) {}

FunctionCall::FunctionCall(const std::string &name, const std::list <Expression> &parameters)
: Expression(NodeType::FunctionCall), name(name), parameters(parameters) {}

IfStatement::IfStatement(const Expression &condition, const std::list <Statement> &thenBody, const std::list <Statement> &elseBody)
: Statement(NodeType::IfStatement), condition(condition), thenBody(thenBody), elseBody(elseBody) {}

AssignmentStatement::AssignmentStatement(const Identifier &variable, const Expression &value)
: Statement(NodeType::AssignmentStatement), variable(variable), value(value) {}

WhileStatement::WhileStatement(const Expression &condition, const std::list <Statement> &body)
: Statement(NodeType::WhileStatement), condition(condition), body(body) {}

