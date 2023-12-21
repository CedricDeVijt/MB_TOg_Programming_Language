//
// Created by Siebe Mees on 21/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

/* TODO: Implement this
 * TEST(ExecutorTest, IfStatementExecution) {
    // Create an environment
    Env env;

    // Create a simple if statement: if (true) { x = 10.0; } else { x = 5.0; }
    auto condition = std::make_unique<Bool>(true);
    auto thenAssignment = std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Float>(10.0));
    auto elseAssignment = std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Float>(5.0));
    IfStatement ifStatement(std::move(condition),
                            std::make_unique<Statement>(std::move(thenAssignment)),
                            std::make_unique<Statement>(std::move(elseAssignment)));

    // Create an executor and execute the if statement
    Executor executor(env);
    executor.evalIfStatement(&ifStatement);

    // Check the value of 'x' in the environment
    auto value = env.get("x");
    EXPECT_EQ(std::get<float>(value), 10.0);
}*/
