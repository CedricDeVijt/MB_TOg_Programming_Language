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

Value Executor::evalExpression(const Expression &expression) {
    return expression.evaluate(env);
}

void Executor::evalAssignment(const Statement& statement) {
    // TODO: Implement
}