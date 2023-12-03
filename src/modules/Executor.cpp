#include "Executor.h"


// Public methods
VariableValue Executor::execute(const Statement *node) {
    executeStatement(node);
    return VariableValue();
}

void Executor::executeFunction(const FunctionDeclaration *node) {
    std::string functionName = node->getName();
    functions[functionName] = node;
}


// Private methods
VariableValue Executor::executeStatement(const Statement *node) {
    switch (node->getKind()) {
        case NodeType::Program:
            return executeProgram((Program *) node);
        case NodeType::FunctionDeclaration:
            return executeProgram((Program *) node);
        case NodeType::IfStatement:
            return executeIfStatement((IfStatement *) node);
        case NodeType::AssignmentStatement:
            return executeAssignmentStatement((AssignmentStatement *) node);
        case NodeType::WhileStatement:
            return executeWhileStatement((WhileStatement *) node);
        default:
            throw std::runtime_error("Unhandled statement type in executeStatement");
    }
    return VariableValue();
}

VariableValue Executor::executeProgram(const Program *node) {
    for (const auto& statement : node->getBody()) {
        executeStatement(&statement);
    }
    return VariableValue();
}

VariableValue Executor::executeExpression(const Expression *node) {
    switch (node->getKind()) {
        case NodeType::BinaryExpression:
            return executeBinaryExpression((BinaryExpression *) node);
        case NodeType::Identifier:
            return executeIdentifier((Identifier *) node);
        case NodeType::Float:
            return executeFloat((Float *) node);
        case NodeType::String:
            return executeString((String *) node);
        case NodeType::Bool:
            return executeBool((Bool *) node);
        case NodeType::FunctionCall:
            return executeFunctionCall((FunctionCall *) node);
        default:
            throw std::runtime_error("Unhandled expression type in executeExpression");
    }
    return VariableValue();
}

VariableValue Executor::executeBinaryExpression(const BinaryExpression *node) {
    auto left = execute(&node->getLeft());
    auto right = execute(&node->getRight());
    auto op = node->getOp();

    if (op == "+") {
        if (left.index() == 0 && right.index() == 0) {
            return std::get<int>(left) + std::get<int>(right);
        } else if (left.index() == 0 && right.index() == 1) {
            return std::get<int>(left) + std::get<double>(right);
        } else if (left.index() == 1 && right.index() == 0) {
            return std::get<double>(left) + std::get<int>(right);
        } else if (left.index() == 1 && right.index() == 1) {
            return std::get<double>(left) + std::get<double>(right);
        } else {
            throw std::runtime_error("Cannot add non-numeric values");
        }
    } else if (op == "-") {
        if (left.index() == 0 && right.index() == 0) {
            return std::get<int>(left) - std::get<int>(right);
        } else if (left.index() == 0 && right.index() == 1) {
            return std::get<int>(left) - std::get<double>(right);
        } else if (left.index() == 1 && right.index() == 0) {
            return std::get<double>(left) - std::get<int>(right);
        } else if (left.index() == 1 && right.index() == 1) {
            return std::get<double>(left) - std::get<double>(right);
        } else {
            throw std::runtime_error("Cannot subtract non-numeric values");
        }
    } else if (op == "*") {
        if (left.index() == 0 && right.index() == 0) {
            return std::get<int>(left) * std::get<int>(right);
        } else if (left.index() == 0 && right.index() == 1) {
            return std::get<int>(left) * std::get<double>(right);
        } else if (left.index() == 1 && right.index() == 0) {
            return std::get<double>(left) * std::get<int>(right);
        } else if (left.index() == 1 && right.index() == 1) {
            return std::get<double>(left) * std::get<double>(right);
        } else {
            throw std::runtime_error("Cannot multiply non-numeric values");
        }
    }

    throw std::runtime_error("Unknown operator");
}

VariableValue Executor::executeIdentifier(const Identifier *node) {
    return currentEnvironment->getVariable(node->getSymbol());
}

VariableValue Executor::executeFloat(const Float *node) {
    return node->getValue();
}

VariableValue Executor::executeString(const String *node) {
    return node->getValue();
}

VariableValue Executor::executeBool(const Bool *node) {
    return node->isValue();
}

VariableValue Executor::executeFunctionCall(const FunctionCall *node) {
    std::string functionName = node->getName();
    auto function = functions.find(functionName);
    if (function == functions.end()) {
        throw std::runtime_error("Function not found: " + functionName);
    }

    const FunctionDeclaration* functionDeclaration = function->second;

    // Create a new scope for function execution
    std::shared_ptr<Environment> localEnvironment = currentEnvironment->createChildScope();

    // Assign argument to parameters
    auto parameters = functionDeclaration->getParameters();
    auto arguments = node->getParameters();

    if (parameters.size() != arguments.size()) {
        throw std::runtime_error("Invalid number of arguments");
    }

    auto paramIt = parameters.begin();
    auto argIt = arguments.begin();
    for (; paramIt != parameters.end() && argIt != arguments.end(); paramIt++, argIt++) {
        localEnvironment->setVariable(paramIt->getSymbol(), execute(&*argIt));
    }

    // Temporarily set currentEnv to localEnv to execute the function body
    auto previousEnvironment = currentEnvironment;
    currentEnvironment = localEnvironment;

    // Execute the function body
    for (const auto& statement : functionDeclaration->getBody()) {
        executeStatement(&statement);
    }

    // Restore the previous environment
    currentEnvironment = previousEnvironment;

    // Return the result of the function
    return localEnvironment->getVariable(functionName);
}

VariableValue Executor::executeIfStatement(const IfStatement *node) {
    auto condition = execute(&node->getCondition());
    if (std::get<bool>(condition)) {
        // Execute the 'then' body
        for (const auto& statement : node->getThenBody()) {
            executeStatement(&statement);
        }
    } else if (!node->getElseBody().empty()) {
        // Execute the 'else' body
        for (const auto& statement : node->getElseBody()) {
            executeStatement(&statement);
        }
    }
    return VariableValue();
}

VariableValue Executor::executeAssignmentStatement(const AssignmentStatement *node) {
    // TODO: Expression value = executeExpression(&node->getValue());
    std::string variableName = node->getVariable().getSymbol();


    // TODO: currentEnvironment->setVariable(variableName, value);
    return VariableValue();
}

VariableValue Executor::executeWhileStatement(const WhileStatement *node) {
    while (std::get<bool>(execute(&node->getCondition()))) {
        for (const auto& statement : node->getBody()) {
            executeStatement(&statement);
        }
    }
    return VariableValue();
}
