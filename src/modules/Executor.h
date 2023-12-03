#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../datatypes/AST.h"
#include "executionEnvironment/Environment.h"

class Executor {
private:
    std::shared_ptr<Environment> currentEnvironment;
    std::map<std::string, const FunctionDeclaration*> functions;


    // Methods for executing statements
    VariableValue executeStatement(const Statement* node);
    VariableValue executeProgram(const Program* node);

    // Methods for executing expressions
    VariableValue executeExpression(const Expression* node);
    // Expressions
    VariableValue executeBinaryExpression(const BinaryExpression* node);
    VariableValue executeIdentifier(const Identifier* node);
    VariableValue executeFloat(const Float* node);
    VariableValue executeString(const String* node);
    VariableValue executeBool(const Bool* node);

    // Statements
    VariableValue executeFunctionCall(const FunctionCall* node);
    VariableValue executeIfStatement(const IfStatement* node);
    VariableValue executeAssignmentStatement(const AssignmentStatement* node);
    VariableValue executeWhileStatement(const WhileStatement* node);
public:
    VariableValue execute(const Statement* node);

    void executeFunction(const FunctionDeclaration* node);
};

#endif