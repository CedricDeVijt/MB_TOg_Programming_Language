//
// Created by Siebe Mees on 17/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

TEST(AssignmentTest, FloatValueAssignment) {
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

TEST(AssignmentTest, FloatValueAssignmentWithExecution) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Creating a program with a simple assignment: x = 5.0
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Float>(5.0))); // std::list::push_back
    Program program(std::move(statements));

    // Execute the program
    auto result = executor.execute(program);
    // Check if the return is 0 like c++
    EXPECT_EQ(std::get<int>(result), 0);

    // Check if the environment has the correct value for 'x'
    Value x = env.get("x");
    EXPECT_EQ(std::get<float>(x), 5.0);
}

TEST(AssignmentTest, BooleanValueAssignment) {
    // Create an environment
    Env env;

    // Create a boolean assignment: flag = true
    AssignmentStatement assignmentStatement(Identifier("flag"), std::make_unique<Bool>(true));

    auto left = assignmentStatement.getVariable();
    auto right = assignmentStatement.getValue();
    auto result = right->evaluate(env);

    EXPECT_EQ(left.getSymbol(), "flag");
    EXPECT_EQ(std::get<bool>(result), true);
}

TEST(AssignmentTest, BooleanValueAssignmentWithExecution) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Creating a program with a boolean assignment: flag = true
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("flag"), std::make_unique<Bool>(true))); // std::list::push_back
    Program program(std::move(statements));

    // Execute the program
    executor.execute(program);

    // Check if the environment has the correct value for 'flag'
    Value flag = env.get("flag");
    EXPECT_EQ(std::get<bool>(flag), true);
}

TEST(AssignmentTest, IntegerValueAssignment) {
    Env env;
    AssignmentStatement assignmentStatement(Identifier("y"), std::make_unique<Integer>(10));

    auto left = assignmentStatement.getVariable();
    auto right = assignmentStatement.getValue();
    auto result = right->evaluate(env);

    EXPECT_EQ(left.getSymbol(), "y");
    EXPECT_EQ(std::get<int>(result), 10);
}

TEST(AssignmentTest, StringValueAssignment) {
    Env env;
    AssignmentStatement assignmentStatement(Identifier("name"), std::make_unique<String>("Alice"));

    auto left = assignmentStatement.getVariable();
    auto right = assignmentStatement.getValue();
    auto result = right->evaluate(env);

    EXPECT_EQ(left.getSymbol(), "name");
    EXPECT_EQ(std::get<std::string>(result), "Alice");
}

TEST(AssignmentTest, CombinedAssignmentAndReturn) {
    Env env;
    Executor executor(env);

    // Assign a value and then return it
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("z"), std::make_unique<Integer>(42)));
    statements.push_back(std::make_unique<ReturnStatement>(std::make_unique<Identifier>("z")));

    Program program(std::move(statements));
    auto result = executor.execute(program);

    EXPECT_EQ(std::get<int>(result), 42);
}
