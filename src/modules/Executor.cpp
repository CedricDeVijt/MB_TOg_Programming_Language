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
    }
}

Value Executor::evalExpression(const Expression &expression) {
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
    auto result = evalExpression(*right);
    env.set(left.getSymbol(), result);
}

void Executor::evalFunctionDeclaration(const Statement *statement) {
    auto funcDecl = dynamic_cast<const FunctionDeclaration*>(statement);
    if (!funcDecl) {
        throw std::runtime_error("Invalid statement type for function declaration");
    }

    std::string functName = funcDecl->getName();
    auto parameters = funcDecl->getParameters();
    auto body = funcDecl->getBody();

    // Create a std::function wrapper around the generic function wrapper
    Function func = [body, parameters, this, functName](const std::vector<Value>& args) -> Value {
        // Check if arguments count matches the parameters count
        if (args.size() != parameters.size()) {
            throw std::runtime_error("Invalid number of arguments passed to function " + functName);
        }

        // TODO: Create a new scope in the environment for the function execution
        // env.pushScope();

        // Set up the environment with arguments
        auto paramIter = parameters.begin();
        auto argIter = args.begin();
        for (; paramIter != parameters.end(); ++paramIter, ++argIter) {
            env.set(paramIter->getSymbol(), *argIter);
        }

        // Execute the function body
        Value returnValue;
        for (const auto& stmt : body) {
            evalStatement(std::make_unique<Statement>(stmt));

            // Handle return statements or other flow controls as needed
            // ...
        }

        // TODO: Pop the function scope
        // env.popScope();

        // Return the result
        return returnValue;
    };

    env.setFunction(functName, func);
}

void Executor::evalBinaryExpression(const Statement* statement) {
    // TODO: Implement this, already done in AST.cpp but wan that code in this file
}