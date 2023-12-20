//
// Created by Siebe Mees on 11/12/2023.
//

#include "Executor.h"

Executor::Executor(Env& env) : env(env) {}

void Executor::execute(const Program& program) {
    for (const auto& statement : program.getBody()) {
        evalStatement(statement);
    }
}

void Executor::evalStatement(const std::unique_ptr<Statement>& statement) {
    switch (statement->getKind()) {
        case NodeType::AssignmentStatement:
            evalAssignment(statement.get());
            break;
        case NodeType::FunctionDeclaration:
            evalFunctionDeclaration(statement.get());
            break;
        case NodeType::ReturnStatement:
            evalReturnStatement(statement.get(), env);
    }
}

Value Executor::evalExpression(const Expression &expression, Env& env) {
    /* TODO: Implement this
     * switch (expression.getKind()) {
        case NodeType::BinaryExpression:
            return evalBinaryExpression();
        default:
            return expression.evaluate(env);
    }*/
    return expression.evaluate(env);
}

void Executor::evalAssignment(const Statement* statement) {
    auto assignmentStatement = dynamic_cast<const AssignmentStatement*>(statement);
    auto left = assignmentStatement->getVariable();
    auto right = assignmentStatement->getValue();
    auto result = evalExpression(*right, env);
    env.set(left.getSymbol(), result);
}

void Executor::evalFunctionDeclaration(const Statement *statement) {
    auto funcDecl = dynamic_cast<const FunctionDeclaration*>(statement);
    if (!funcDecl) {
        throw std::runtime_error("Invalid statement type for function declaration");
    }

    std::string functName = funcDecl->getName();
    const auto& parameters = funcDecl->getParameters();
    const auto& body = funcDecl->getBody();

    // Create a std::function wrapper around the generic function wrapper
    Function func = [&body, &parameters, this, &functName](const std::vector<Value>& args) -> Value {
        // Check if arguments count matches the parameters count
        if (args.size() != parameters.size()) {
            throw std::runtime_error("Invalid number of arguments passed to function " + functName);
        }

        // Create a new scope for function execution
        Env newEnv(env); // env is the current environment

        // Set up arguments in the new scope
        auto paramIter = parameters.begin();
        auto argIter = args.begin();
        for (; paramIter != parameters.end(); ++paramIter, ++argIter) {
            newEnv.set(paramIter->get()->getSymbol(), *argIter);
        }

        // Execute each statement in the function body
        Value returnValue;
        for (const auto& stmt : body) {
            if (stmt->getKind() == NodeType::ReturnStatement) {
                returnValue = evalReturnStatement(stmt.get(), newEnv);
                break;
            }
            evalStatement(stmt);
        }

        return returnValue;
    };


    env.setFunction(functName, func);
}

void Executor::evalBinaryExpression(const Statement* statement) {
    // TODO: Implement this, already done in AST.cpp but wan that code in this file
}

Value Executor::evalReturnStatement(const Statement* statement, Env& newEnv) {// Dynamic cast to ensure statement is a ReturnStatement
    auto returnStatement = dynamic_cast<const ReturnStatement*>(statement);
    if (!returnStatement) {
        throw std::runtime_error("Expected a ReturnStatement");
    }

    // Assuming ReturnStatement has a method to get its expression
    const Expression* returnExpression = returnStatement->getExpression();
    if (!returnExpression) {
        throw std::runtime_error("ReturnStatement has no expression");
    }

    // Evaluate the expression in the context of newEnv
    // Assuming evalExpression is a method that takes an Expression and an Env
    return evalExpression(*returnExpression, newEnv);
}