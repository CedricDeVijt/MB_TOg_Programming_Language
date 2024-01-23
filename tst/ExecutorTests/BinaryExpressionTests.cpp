//
// Created by Siebe Mees on 17/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

// Test for addition in BinaryExpression
TEST(BinaryExpressionTest, Addition) {
    // Create an environment
    Env env;

    // Creating a simple binary expression: 5.0 + 5.0
    std::unique_ptr<Statement> left = std::make_unique<Float>(5.0);
    std::unique_ptr<Statement> right = std::make_unique<Float>(5.0);
    std::string op = "+";
    BinaryExpression binaryexpression(std::move(left), std::move(right), op);

    auto result = binaryexpression.evaluate(env);

    EXPECT_EQ(std::get<float>(result), 10.0);
}

TEST(BinaryExpressionTest, AdditionWithExecution) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Creating a program with a simple binary expression: x = 5.0 + 5.0
    std::list<std::unique_ptr<Statement>> statements;
    std::unique_ptr<BinaryExpression> binaryexpression = std::make_unique<BinaryExpression>(std::make_unique<Float>(5.0), std::make_unique<Float>(5.0), "+");
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::move(binaryexpression))); // std::list::push_back
    Program program(std::move(statements));

    // Execute the program
    executor.execute(program);

    // Check if the environment has the correct value for 'x'
    Value x = env.get("x");
    EXPECT_EQ(std::get<float>(x), 10.0);
}

// Test for subtraction in BinaryExpression
TEST(BinaryExpressionTest, Subtraction) {
    // Create an environment
    Env env;

    // Creating a simple binary expression: 10.0 - 5.0
    std::unique_ptr<Statement> left = std::make_unique<Float>(10.0);
    std::unique_ptr<Statement> right = std::make_unique<Float>(5.0);
    std::string op = "-";
    BinaryExpression binaryExpression(std::move(left), std::move(right), op);

    auto result = binaryExpression.evaluate(env);

    EXPECT_EQ(std::get<float>(result), 5.0);
}

// Test for subtraction in BinaryExpression with Executor
TEST(BinaryExpressionTest, SubtractionWithExecution) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Creating a program with a simple binary expression: x = 10.0 - 5.0
    std::list<std::unique_ptr<Statement>> statements;
    std::unique_ptr<BinaryExpression> binaryExpression = std::make_unique<BinaryExpression>(std::make_unique<Float>(10.0), std::make_unique<Float>(5.0), "-");
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::move(binaryExpression)));
    Program program(std::move(statements));

    // Execute the program
    executor.execute(program);

    // Check if the environment has the correct value for 'x'
    Value x = env.get("x");
    EXPECT_EQ(std::get<float>(x), 5.0);
}

// Test for multiplication in BinaryExpression
TEST(BinaryExpressionTest, Multiplication) {
    // Create an environment
    Env env;

    // Creating a simple binary expression: 3.0 * 4.0
    std::unique_ptr<Statement> left = std::make_unique<Float>(3.0);
    std::unique_ptr<Statement> right = std::make_unique<Float>(4.0);
    std::string op = "*";
    BinaryExpression binaryExpression(std::move(left), std::move(right), op);

    auto result = binaryExpression.evaluate(env);

    EXPECT_EQ(std::get<float>(result), 12.0);
}

// Test for multiplication in BinaryExpression with Executor
TEST(BinaryExpressionTest, MultiplicationWithExecution) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Creating a program with a simple binary expression: x = 3.0 * 4.0
    std::list<std::unique_ptr<Statement>> statements;
    std::unique_ptr<BinaryExpression> binaryExpression = std::make_unique<BinaryExpression>(std::make_unique<Float>(3.0), std::make_unique<Float>(4.0), "*");
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::move(binaryExpression)));
    Program program(std::move(statements));

    // Execute the program
    executor.execute(program);

    // Check if the environment has the correct value for 'x'
    Value x = env.get("x");
    EXPECT_EQ(std::get<float>(x), 12.0);
}

// Test for division in BinaryExpression
TEST(BinaryExpressionTest, Division) {
    // Create an environment
    Env env;

    // Creating a simple binary expression: 8.0 / 2.0
    std::unique_ptr<Statement> left = std::make_unique<Float>(8.0);
    std::unique_ptr<Statement> right = std::make_unique<Float>(2.0);
    std::string op = "/";
    BinaryExpression binaryExpression(std::move(left), std::move(right), op);

    auto result = binaryExpression.evaluate(env);

    EXPECT_EQ(std::get<float>(result), 4.0);
}

// Test for division in BinaryExpression with Executor
TEST(BinaryExpressionTest, DivisionWithExecution) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Creating a program with a simple binary expression: x = 8.0 / 2.0
    std::list<std::unique_ptr<Statement>> statements;
    std::unique_ptr<BinaryExpression> binaryExpression = std::make_unique<BinaryExpression>(std::make_unique<Float>(8.0), std::make_unique<Float>(2.0), "/");
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::move(binaryExpression)));
    Program program(std::move(statements));

    // Execute the program
    executor.execute(program);

    // Check if the environment has the correct value for 'x'
    Value x = env.get("x");
    EXPECT_EQ(std::get<float>(x), 4.0);
}

// Test for modulo in BinaryExpression with previvious assignment
TEST(BinaryExpressionTest, WithPreviousAssignment) {
    // Create an environment
    Env env;

    // Creating a simple assignment: x = 8.5
    float x = 8.5;
    env.set("x", x);
    // Creating a simple binary expression: x + 3.5
    std::unique_ptr<BinaryExpression> binaryExpression = std::make_unique<BinaryExpression>(std::make_unique<Identifier>("x"), std::make_unique<Float>(3.5), "+");
    auto result = binaryExpression.get()->evaluate(env);

    EXPECT_EQ(std::get<float>(result), 12.0);
}

