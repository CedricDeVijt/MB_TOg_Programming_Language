#include "AST.h"

Statement::Statement(NodeType kind)
: kind(kind) {}

NodeType Statement::getKind() const {
    return kind;
}

Program::Program(std::list<std::unique_ptr<Statement>>&& body)
        : Statement(NodeType::Program), body(std::move(body)) {}

const std::list<std::unique_ptr<Statement>>& Program::getBody() const {
    return body;
}

Expression::Expression(NodeType kind)
: Statement(kind) {}

BinaryExpression::BinaryExpression(std::unique_ptr<Statement> left, std::unique_ptr<Statement> right, std::string op)
: Expression(NodeType::BinaryExpression), left(std::move(left)), right(std::move(right)), op(std::move(op)) {}

Value BinaryExpression::evaluate(Env &env) const {
    Value leftValue = dynamic_cast<const Expression*>(left.get())->evaluate(env);
    Value rightValue = dynamic_cast<const Expression*>(right.get())->evaluate(env);

    return std::visit([this](auto&& lhs, auto&& rhs) -> Value {
        using LHSType = std::decay_t<decltype(lhs)>;
        using RHSType = std::decay_t<decltype(rhs)>;
        if constexpr (std::is_same_v<LHSType, RHSType>) {
            if constexpr (std::is_arithmetic_v<LHSType>) {
                if (op == "+") {
                    return lhs + rhs;
                } else if (op == "-") {
                    return lhs - rhs;
                } else if (op == "*") {
                    return lhs * rhs;
                } else if (op == "/") {
                    if (rhs == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    return lhs / rhs;
                }
                // ... other operators
            } else {
                throw std::runtime_error("Unsupported operation for non-arithmetic types");
            }
        } else {
            throw std::runtime_error("Type mismatch in binary expression");
        }
    }, leftValue, rightValue);
}

const Statement* BinaryExpression::getLeft() const {
    return left.get();
}

const Statement* BinaryExpression::getRight() const {
    return right.get();
}

const std::string &BinaryExpression::getOp() const {
    return op;
}

Identifier::Identifier(const std::string &symbol) : Expression(NodeType::Identifier), symbol(symbol) {}

Value Identifier::evaluate(Env &env) const {
    return getSymbol();
}

const std::string &Identifier::getSymbol() const {
    return symbol;
}

Float::Float(float value) : Expression(NodeType::Float), value(value) {}

Value Float::evaluate(Env &env) const {
    return getValue();
}

float Float::getValue() const {
    return value;
}

String::String(const std::string &value) : Expression(NodeType::String), value(value) {}

Value String::evaluate(Env &env) const {
    return getValue();
}

const std::string &String::getValue() const {
    return value;
}

Bool::Bool(bool value) : Expression(NodeType::Bool), value(value) {}

Value Bool::evaluate(Env &env) const {
    return isValue();
}

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

FunctionCall::FunctionCall(const std::string &name, std::list<std::unique_ptr<Expression>>&& parameters)
: Expression(NodeType::FunctionCall), name(name), parameters(std::move(parameters)) {}

Value FunctionCall::evaluate(Env &env) const {
    return Value(); // TODO: Implement
    /*
     * // Step 1: Retrieve the function from the environment
    auto function = env.getFunction(name); // Assume getFunction retrieves function objects

    if (!function) {
        throw std::runtime_error("Function " + name + " not found");
    }

    // Step 2: Evaluate each parameter
    std::vector<Value> evaluatedParams;
    for (const auto& param : parameters) {
        evaluatedParams.push_back(param->evaluate(env));
    }

    // Step 3: Execute the function with evaluated parameters
    // Assuming executeFunction is a method in Env to execute functions
    return env.executeFunction(function, evaluatedParams);
     */
}

const std::string &FunctionCall::getName() const {
    return name;
}

const std::list<std::unique_ptr<Expression>>& FunctionCall::getParameters() const {
    return parameters;
}

IfStatement::IfStatement(std::unique_ptr<Expression> condition, const std::list<Statement>& thenBody, const std::list<Statement>& elseBody)
: Statement(NodeType::IfStatement), condition(std::move(condition)), thenBody(thenBody), elseBody(elseBody) {}

const Expression& IfStatement::getCondition() const {
    return *condition;
}

const std::list<Statement> &IfStatement::getThenBody() const {
    return thenBody;
}

const std::list<Statement> &IfStatement::getElseBody() const {
    return elseBody;
}

AssignmentStatement::AssignmentStatement(const Identifier id, std::unique_ptr<Expression> expr)
: Statement(NodeType::AssignmentStatement), variable(std::move(id)), value(std::move(expr)) {}


const Identifier &AssignmentStatement::getVariable() const {
    return variable;
}

const Expression* AssignmentStatement::getValue() const {
    return value.get();
}

WhileStatement::WhileStatement(std::unique_ptr<Expression> condition, const std::list<Statement>& body)
: Statement(NodeType::WhileStatement), condition(std::move(condition)), body(body) {}

const Expression &WhileStatement::getCondition() const {
    return *condition;
}

const std::list<Statement> &WhileStatement::getBody() const {
    return body;
}

