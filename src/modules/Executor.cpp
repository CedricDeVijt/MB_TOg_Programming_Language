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

void Executor::evalStatement(const Statement& statement) {
    switch (statement.getKind()) {
        case NodeType::AssignmentStatement:
            evalAssignment(statement);
            break;
    }
}

float Executor::evalExpression(const Expression& expression) {
    switch (expression.getKind()) {
        case NodeType::Float:
            // TODO: evalFloat(expression);
            const auto &floatValue = static_cast<const Float &>(expression);
            return floatValue.getValue();
            break;
    }
}

void Executor::evalAssignment(const Statement& statement) {
    const auto &assignment = static_cast<const AssignmentStatement &>(statement);

    const auto &lhs = assignment.getVariable();
    const auto &rhs = assignment.getValue();

    auto value = evalExpression(rhs);

    env.set(lhs.getSymbol(), std::to_string(value));
}