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
    Value evalExpression(const Expression& expression);

    void evalAssignment(const Statement* statement);
    void evalBinaryExpression(const Statement* statement);

public:
    explicit Executor(Env& env);

    void execute(const Program& program);

};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_EXECUTOR_H
