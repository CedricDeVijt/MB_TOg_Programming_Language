//
// Created by Siebe Mees on 19/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

// Test for a simple add function declaration
TEST(FunctionDeclarationTest, SimpleAddFunctionDeclaration) {
    // Create environment and executor
    Env env;
    Executor executor(env);

    // Create a function declaration
    std::string functionName = "add";
    std::list<std::unique_ptr<Identifier>> parameters;
    parameters.push_back(std::make_unique<Identifier>("x"));

    std::list<std::unique_ptr<Statement>> functionBody;
    // Wrap the binary expression in a return statement
    functionBody.push_back(std::make_unique<ReturnStatement>(
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("x"), std::make_unique<Integer>(1), "+"
            )
    ));

    auto functionDecl = std::make_unique<FunctionDeclaration>(functionName, std::move(parameters), std::move(functionBody));

    // Create a program with the function declaration
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(functionDecl));
    Program program(std::move(programBody));
    Value result = executor.execute(program);
    EXPECT_EQ(std::get<int>(result), 0);
    EXPECT_TRUE(env.containsFunction("add"));
}


TEST(FunctionDeclarationTest, SimpleAddFunctionDeclarationWithExecution) {
    // Create environment and executor
    Env env;
    Executor executor(env);

    // Create a function declaration
    std::string functionName = "add";
    std::list<std::unique_ptr<Identifier>> parameters;
    parameters.push_back(std::make_unique<Identifier>("x"));

    std::list<std::unique_ptr<Statement>> functionBody;
    // Wrap the binary expression in a return statement
    functionBody.push_back(std::make_unique<ReturnStatement>(
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("x"), std::make_unique<Integer>(1), "+"
            )
    ));

    auto functionDecl = std::make_unique<FunctionDeclaration>(functionName, std::move(parameters), std::move(functionBody));

    // Create a program with the function declaration
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(functionDecl));
    Program program(std::move(programBody));
    executor.execute(program);
    EXPECT_TRUE(env.containsFunction("add"));

    // Create a function call to 'add' with one integer argument
    Value result = env.executeFunction("add", std::vector<Value>{5});
    EXPECT_EQ(std::get<int>(result), 6);
}

TEST(FunctionDeclarationTest, ComplexCalculateFunctionWithExecution) {
    // Create environment and executor
    Env env;
    Executor executor(env);

    // Create a function declaration
    std::string functionName = "calculate";
    std::list<std::unique_ptr<Identifier>> parameters;
    parameters.push_back(std::make_unique<Identifier>("a"));
    parameters.push_back(std::make_unique<Identifier>("b"));

    // Create a function body with multiple operations
    std::list<std::unique_ptr<Statement>> functionBody;
    auto addExpr = std::make_unique<BinaryExpression>(
            std::make_unique<Identifier>("a"), std::make_unique<Identifier>("b"), "+");
    auto mulExpr = std::make_unique<BinaryExpression>(
            std::move(addExpr), std::make_unique<Integer>(2), "*");
    functionBody.push_back(std::make_unique<ReturnStatement>(std::move(mulExpr)));

    auto functionDecl = std::make_unique<FunctionDeclaration>(functionName, std::move(parameters), std::move(functionBody));

    // Create a program with the function declaration
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(functionDecl));
    Program program(std::move(programBody));
    executor.execute(program);
    EXPECT_TRUE(env.containsFunction("calculate"));

    // Create a function call to 'calculate' with two integer arguments
    Value result = env.executeFunction("calculate", std::vector<Value>{3, 4}); // 3 + 4 = 7, 7 * 2 = 14
    EXPECT_EQ(std::get<int>(result), 14);
}

