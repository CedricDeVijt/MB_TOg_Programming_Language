//
// Created by Siebe Mees on 11/12/2023.
//

#ifndef MB_TOG_PROGRAMMING_LANGUAGE_EXECUTOR_H
#define MB_TOG_PROGRAMMING_LANGUAGE_EXECUTOR_H

#include "executionEnvironment/Environment.h"
#include "datatypes/AST.h"

class Executor {
private:
    Env& env;

    void evalStatement(const std::unique_ptr<Statement>& statement);
    Value evalExpression(const Expression& expression, Env& env);

    void evalAssignment(const Statement* statement);
    void evalFunctionDeclaration(const Statement* statement);
    void evalBinaryExpression(const Statement* statement);
    Value evalReturnStatement(const Statement* statement, Env& newEnv);
    void evalIfStatement(const Statement* statement);

public:
    explicit Executor(Env& env);

    Value execute(const Program& program);

};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_EXECUTOR_H
