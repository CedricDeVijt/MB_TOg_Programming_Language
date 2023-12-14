//
// Created by Siebe Mees on 14/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

TEST(ExecutorTest, Assignment) {
    // Create an environment
    Env env;

    // Creating a simple assignment: x = 5.0
    AssignmentStatement assignmentStatement(Identifier("x"), std::make_unique<Float>(5.0));

    auto left = assignmentStatement.getVariable();
    auto right = assignmentStatement.getValue();
    auto result = right->evaluate(env);

    EXPECT_EQ(left.getSymbol(), "x");
    EXPECT_EQ(std::get<float>(result), 5.0);
}

TEST(ExecutorTest, AssignmentWithExecution) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Creating a program with a simple assignment: x = 5.0
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Float>(5.0))); // std::list::push_back
    Program program(std::move(statements));

    // Execute the program
    executor.execute(program);

    // Check if the environment has the correct value for 'x'
    EXPECT_EQ(env.get("x"), "5.000000");
}