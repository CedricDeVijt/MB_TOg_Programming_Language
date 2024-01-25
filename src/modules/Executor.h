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
    Value returnValue = 0; // Because an statement is not an expression, we need to store the last evaluated value, so when we have e.g. an if statement, we can return the last evaluated valueant our thenbody is an resturnstatement we don't reutrn the value of the statement

    void evalStatement(const std::unique_ptr<Statement>& statement);
    Value evalExpression(const Expression& expression, Env& env);

    void evalAssignment(const Statement* statement);
    void evalFunctionDeclaration(const Statement* statement);
    void evalBinaryExpression(const Statement* statement);
    Value evalReturnStatement(const Statement* statement, Env& newEnv);
    void evalIfStatement(const Statement* statement);
    void evalWhileStatement(const Statement* statement);
    /*void evalPrintStatement(const Statement* statement);
    void evalInputStatement(const Statement* statement);*/

public:
    explicit Executor(Env& env);

    Value execute(const Program& program);

};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_EXECUTOR_H
