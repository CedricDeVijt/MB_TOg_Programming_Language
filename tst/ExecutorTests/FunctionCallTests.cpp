//
// Created by Siebe Mees on 17/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

// Define a simple function for testing
float add(float x) {
    return x + 1;
}

// Test for a simple function call
TEST(FunctionCallTest, SimpleFunctionCall) {
    // Create an environment and define a simple function
    Env env;
    env.setFunction("add", Function(add));

    // Create a function call to 'add' with one float argument
    std::unique_ptr<Expression> arg1 = std::make_unique<Float>(3.0);
    std::list<std::unique_ptr<Expression>> args;
    args.push_back(std::move(arg1));
    FunctionCall functionCall("add", std::move(args));

    // Evaluate the function call
    Value result = functionCall.evaluate(env);

    // Check the result
    EXPECT_EQ(std::get<float>(result), 4.0); // Expecting 3.0 + 1.0 = 4.0
}

// Define a simple function for testing
int subtract(int x) {
    return x - 1;
}

// Test for a simple function call
TEST(FunctionCallTest, IntegerFunctionCall) {
    // Create an environment and define a simple function
    Env env;
    env.setFunction("subtract", Function(subtract));

    // Create a function call to 'subtract' with one integer argument
    std::unique_ptr<Expression> arg1 = std::make_unique<Integer>(5);
    std::list<std::unique_ptr<Expression>> args;
    args.push_back(std::move(arg1));
    FunctionCall functionCall("subtract", std::move(args));

    // Evaluate the function call
    Value result = functionCall.evaluate(env);

    // Check the result
    EXPECT_EQ(std::get<int>(result), 4); // Expecting 5 - 1
}

// Define a simple function for testing
std::string greet(std::string name) {
    return "Hello, " + name;
}

// Test for a simple function call
TEST(FunctionCallTest, StringFunctionCall) {
    // Create an environment and define a simple function
    Env env;
    env.setFunction("greet", Function(greet));

    // Create a function call to 'greet' with one string argument
    std::unique_ptr<Expression> arg1 = std::make_unique<String>("World");
    std::list<std::unique_ptr<Expression>> args;
    args.push_back(std::move(arg1));
    FunctionCall functionCall("greet", std::move(args));

    // Evaluate the function call
    Value result = functionCall.evaluate(env);

    // Check the result
    EXPECT_EQ(std::get<std::string>(result), "Hello, World");
}

// Define a simple function for testing
bool isPositive(int x) {
    return x > 0;
}

// Test for a simple function call
TEST(FunctionCallTest, BooleanFunctionCall) {
    // Create an environment and define a simple function
    Env env;
    env.setFunction("isPositive", Function(isPositive));

    // Create a function call to 'isPositive' with one integer argument
    std::unique_ptr<Expression> arg1 = std::make_unique<Integer>(-1);
    std::list<std::unique_ptr<Expression>> args;
    args.push_back(std::move(arg1));
    FunctionCall functionCall("isPositive", std::move(args));

    // Evaluate the function call
    Value result = functionCall.evaluate(env);

    // Check the result
    EXPECT_EQ(std::get<bool>(result), false); // Expecting false for -1
}

