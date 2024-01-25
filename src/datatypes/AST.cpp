#include "AST.h"
#include <sstream>
#include <variant>

Statement::Statement(NodeType kind)
: kind(kind) {}

NodeType Statement::getKind() const {
    return kind;
}

Program::Program(std::list<std::unique_ptr<Statement>> body)
        : Statement(NodeType::Program), body(std::move(body)) {}

const std::list<std::unique_ptr<Statement>>& Program::getBody() const {
    return body;
}

void Program::push_back(std::unique_ptr<Statement> statement) {
    body.push_back(std::move(statement));
}

Expression::Expression(NodeType kind)
: Statement(kind) {}

BinaryExpression::BinaryExpression(std::unique_ptr<Statement> left, std::unique_ptr<Statement> right, std::string op)
: Expression(NodeType::BinaryExpression), left(std::move(left)), right(std::move(right)), op(std::move(op)) {}

Value BinaryExpression::evaluate(Env &env) const {
    // Evaluate the left side of the expression
    Value leftValue;
    if (left->getKind() == NodeType::Identifier) {
        std::string symbol = dynamic_cast<const Identifier*>(left.get())->getSymbol();
        if (!env.contains(symbol)) {
            throw std::runtime_error("Undefined variable: " + symbol);
        }
        leftValue = env.get(symbol);
    } else {
        leftValue = dynamic_cast<const Expression*>(left.get())->evaluate(env);
    }

    // Evaluate the right side of the expression
    Value rightValue;
    if (right->getKind() == NodeType::Identifier) {
        std::string symbol = dynamic_cast<const Identifier*>(right.get())->getSymbol();
        if (!env.contains(symbol)) {
            throw std::runtime_error("Undefined variable: " + symbol);
        }
        rightValue = env.get(symbol);
    } else {
        rightValue = dynamic_cast<const Expression*>(right.get())->evaluate(env);
    }

    return std::visit([this](auto&& lhs, auto&& rhs) -> Value {
        using LHSType = std::decay_t<decltype(lhs)>;
        using RHSType = std::decay_t<decltype(rhs)>;
        // Check if both types are the same
        if constexpr (std::is_same_v<LHSType, RHSType>) {
            // Arithmetic operations
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
                } else if (op == "%") {
                    // Ensure lhs and rhs are integers for modulo operation
                    if constexpr (std::is_integral_v<LHSType>) {
                        return lhs % rhs;
                    } else {
                        throw std::runtime_error("Modulo operation is not supported for non-integer types");
                    }
                } else if (op == "<") {
                    return lhs < rhs;
                } else if (op == ">") {
                    return lhs > rhs;
                } else if (op == "<=") {
                    return lhs <= rhs;
                } else if (op == ">=") {
                    return lhs >= rhs;
                } else if (op == "==") {
                    return lhs == rhs;
                } else if (op == "!=") {
                    return lhs != rhs;
                } else {
                    throw std::runtime_error("Unsupported operation");
                }
            // String operations
            } else if constexpr (std::is_same_v<LHSType, std::string>) {
                if (op == "+") {
                    return lhs + rhs;
                } else {
                    throw std::runtime_error("Unsupported operation for strings");
                }
            // Boolean operations
            } else if constexpr (std::is_same_v<LHSType, bool>) {
                if (op == "&&") {
                    return lhs && rhs;
                } else if (op == "||") {
                    return lhs || rhs;
                } else {
                    throw std::runtime_error("Unsupported operation for booleans");
                }
            }
            // Default case
            else {
                throw std::runtime_error("Unsupported operation for non-arithmetic types");
            }
        } else {
            throw std::runtime_error("Type mismatch in binary expression");
        }
    }, leftValue, rightValue);
}

const std::unique_ptr<Statement>& BinaryExpression::getLeft() const {
    return left;
}

const std::unique_ptr<Statement>& BinaryExpression::getRight() const {
    return right;
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

Integer::Integer(int value) : Expression(NodeType::Integer), value(value) {}

Value Integer::evaluate(Env &env) const {
    // TODO: Do check in the scope for existing items for everry expression exepct for the binary expression
    return getValue();
}

int Integer::getValue() const {
    return value;
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

FunctionDeclaration::FunctionDeclaration(const std::string& name, std::list<std::unique_ptr<Identifier>>&& parameters, std::list<std::unique_ptr<Statement>>&& body)
: Statement(NodeType::FunctionDeclaration), name(name), parameters(std::move(parameters)), body(std::move(body)) {}

const std::string &FunctionDeclaration::getName() const {
    return name;
}

const std::list<std::unique_ptr<Identifier>> &FunctionDeclaration::getParameters() const {
    return parameters;
}

const std::list<std::unique_ptr<Statement>> &FunctionDeclaration::getBody() const {
    return body;
}

FunctionCall::FunctionCall(const std::string &name, std::list<std::unique_ptr<Expression>>&& parameters)
: Expression(NodeType::FunctionCall), name(name), parameters(std::move(parameters)) {}

Value FunctionCall::evaluate(Env &env) const {
    // Step 1: Retrieve the function from the environment
    if (!env.containsFunction(name)) {
        throw std::runtime_error("Function " + name + " not found or is undefined");
    }
    const Function& function = env.getFunction(name);

    // Step 2: Evaluate each parameter
    std::vector<Value> evaluatedParams;
    for (const auto& param : parameters) {
        evaluatedParams.push_back(param->evaluate(env));
    }

    // Step 3: Execute the function with evaluated parameters
    return function(evaluatedParams);
}

const std::string &FunctionCall::getName() const {
    return name;
}

const std::list<std::unique_ptr<Expression>>& FunctionCall::getParameters() const {
    return parameters;
}

IfStatement::IfStatement(std::unique_ptr<Expression> condition, std::list<std::unique_ptr<Statement>> thenBody, std::unique_ptr<Statement> elseBody)
: Statement(NodeType::IfStatement), condition(std::move(condition)), thenBody(std::move(thenBody)), elseBody(std::move(elseBody)) {}

const std::unique_ptr<Expression>& IfStatement::getCondition() const {
    return condition;
}

const std::list<std::unique_ptr<Statement>> &IfStatement::getThenBody() const {
    return thenBody;
}

const std::unique_ptr<Statement>& IfStatement::getElseBody() const {
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

WhileStatement::WhileStatement(std::unique_ptr<Expression> condition, std::list<std::unique_ptr<Statement>> body)
: Statement(NodeType::WhileStatement), condition(std::move(condition)), body(std::move(body)) {}

const std::unique_ptr<Expression> &WhileStatement::getCondition() const {
    return condition;
}

const std::list<std::unique_ptr<Statement>> &WhileStatement::getBody() const {
    return body;
}

ReturnStatement::ReturnStatement(std::unique_ptr<Expression> expr)
: Statement(NodeType::ReturnStatement), expression(std::move(expr)) {}


const Expression* ReturnStatement::getExpression() const {
    return expression.get();
}

Value ReturnStatement::evaluate(Env& env) const {
    return expression->evaluate(env);
}

/*PrintStatement::PrintStatement(std::unique_ptr<Statement> expression)
: Statement(NodeType::PrintStatement), expression(std::move(expression)) {}

std::string variantToString(const std::variant<float, int, std::string, bool>& var) {
    std::ostringstream ss;
    std::visit([&ss](auto&& arg) {
        using T = std::decay_t<decltype(arg)>; // This extracts the type of arg
        if constexpr (std::is_same_v<T, bool>) {
            ss << std::boolalpha << arg; // Use boolalpha for boolean values
        } else {
            ss << arg; // Use regular output for other types
        }
    }, var);
    return ss.str();
}

void PrintStatement::execute(Env &env) const {
    Value val = dynamic_cast<Expression*>(expression.get())->evaluate(env);
    std::cout << variantToString(val) << std::endl;
}

InputStatement::InputStatement(const std::string& variableName)
: Statement(NodeType::InputStatement), variableName(variableName) {}

void InputStatement::execute(Env &env) const {
    std::string inputLine;
    std::getline(std::cin, inputLine); // This reads the entire line until a newline character is encountered
    env.set(variableName, Value(inputLine));  // Assuming Value can store strings
}*/