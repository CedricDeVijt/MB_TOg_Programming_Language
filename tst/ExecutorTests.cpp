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
    // Create an executor
    Executor executor(env);

    // Creating a simple assignment: x = 5.0
    AssignmentStatement assignmentStatement(Identifier("x"), std::make_unique<Float>(5.0));

    // Creating a program with the assignment statement
    std::list<Statement> statements = {assignmentStatement};
    Program program(statements);

    // Execute the program
    executor.execute(program);

    // Check if the environment has the correct value for 'x'
    EXPECT_EQ(env.get("x"), "5.0");
}