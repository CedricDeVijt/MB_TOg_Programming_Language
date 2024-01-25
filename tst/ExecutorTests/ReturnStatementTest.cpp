//
// Created by Siebe Mees on 21/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

TEST(ReturnTest, BasicReturnTest) {
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

TEST(ReturnTest, ReturnLiteralValueTest) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Create a program that returns a literal value
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<ReturnStatement>(std::make_unique<Integer>(42)));

    Program program(std::move(statements));

    // Execute the program
    Value result = executor.execute(program);

    // Check if the result is the literal value 42
    EXPECT_EQ(std::get<int>(result), 42);
}

TEST(ReturnTest, ReturnBooleanExpressionTest) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Create a program that returns the result of a boolean expression
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<ReturnStatement>(std::make_unique<BinaryExpression>(std::make_unique<Integer>(10), std::make_unique<Integer>(20), "<")));

    Program program(std::move(statements));

    // Execute the program
    Value result = executor.execute(program);

    // Check if the result is true (10 < 20)
    EXPECT_EQ(std::get<bool>(result), true);
}

TEST(ReturnTest, ReturnStringConcatenationTest) {
    // Create an environment
    Env env;
    // Create an executor
    Executor executor(env);

    // Create a program that returns the result of string concatenation
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<ReturnStatement>(std::make_unique<BinaryExpression>(std::make_unique<String>("Hello, "), std::make_unique<String>("World!"), "+")));

    Program program(std::move(statements));

    // Execute the program
    Value result = executor.execute(program);

    // Check if the result is "Hello, World!"
    EXPECT_EQ(std::get<std::string>(result), "Hello, World!");
}

TEST(ReturnTest, ReturnComplexArithmeticExpression) {
    Env env;
    Executor executor(env);

    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<ReturnStatement>(
            std::make_unique<BinaryExpression>(
                    std::make_unique<BinaryExpression>(
                            std::make_unique<Integer>(10),
                            std::make_unique<Integer>(5),
                            "+"
                    ),
                    std::make_unique<Integer>(2),
                    "*"
            )
    ));

    Program program(std::move(statements));
    Value result = executor.execute(program);
    EXPECT_EQ(std::get<int>(result), 30); // (10 + 5) * 2 = 30
}

TEST(ReturnTest, ReturnConditionalExpression) {
    Env env;
    Executor executor(env);

    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<ReturnStatement>(
            std::make_unique<BinaryExpression>(
                    std::make_unique<Integer>(10),
                    std::make_unique<Integer>(10),
                    "=="
            )
    ));

    Program program(std::move(statements));
    Value result = executor.execute(program);
    EXPECT_EQ(std::get<bool>(result), true); // 10 == 10
}

TEST(ReturnTest, ReturnNestedExpressionWithVariables) {
    Env env;
    Executor executor(env);

    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Integer>(5)));
    statements.push_back(std::make_unique<AssignmentStatement>(Identifier("y"), std::make_unique<Integer>(3)));
    statements.push_back(std::make_unique<ReturnStatement>(
            std::make_unique<BinaryExpression>(
                    std::make_unique<BinaryExpression>(
                            std::make_unique<Identifier>("x"),
                            std::make_unique<Identifier>("y"),
                            "+"
                    ),
                    std::make_unique<Integer>(2),
                    "*"
            )
    ));

    Program program(std::move(statements));
    Value result = executor.execute(program);
    EXPECT_EQ(std::get<int>(result), 16); // (x + y) * 2 = (5 + 3) * 2 = 16
}
