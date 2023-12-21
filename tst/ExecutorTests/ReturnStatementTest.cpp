//
// Created by Siebe Mees on 21/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"


TEST(ExecutorTest, ReturnTest) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Create a program
    std::list<std::unique_ptr<Statement>> statements;
    // x = 5.0
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Float>(5.0))); // std::list::push_back
    // y = 10.0
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("y"), std::make_unique<Float>(10.0))); // std::list::push_back
    // return x + y
    statements.push_back(std::make_unique<ReturnStatement>(std::make_unique<BinaryExpression>(std::make_unique<Identifier>("x"), std::make_unique<Identifier>("y"), "+"))); // std::list::push_back
    Program program(std::move(statements));

    // Execute the program
    Value result = executor.execute(program);
    // Check if the environment has the correct value for 'x'
    Value x = env.get("x");
    EXPECT_EQ(std::get<float>(x), 5.0);
    // Check if the environment has the correct value for 'y'
    Value y = env.get("y");
    EXPECT_EQ(std::get<float>(y), 10.0);
    // Check if the result is correct
    EXPECT_EQ(std::get<float>(result), 15.0);


}