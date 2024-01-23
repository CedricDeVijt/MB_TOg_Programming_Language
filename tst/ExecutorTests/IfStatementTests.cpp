//
// Created by Siebe Mees on 21/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

TEST(IfStatementTest, IfStatementThenBodyTest) {
    // Create an environment
    Env env;

    // Create a condition (e.g., true)
    std::unique_ptr<Expression> condition = std::make_unique<Bool>(true);

    // Create 'then' block (e.g., x = 10)
    std::list<std::unique_ptr<Statement>> thenBody;
    thenBody.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Integer>(10)));

    // Create 'else' block (e.g., x = 20), not executed in this test
    std::unique_ptr<Statement> elseBody = std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Integer>(20));

    // Create the IfStatement
    auto ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(thenBody), std::move(elseBody));

    // Create a Program containing the IfStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(ifStatement));

    Program program(std::move(programBody));

    // Create an Executor and execute the program
    Executor executor(env);
    Value programResult = executor.execute(program);
    // Check if the return is 0 like c++, beacuse the program is executed without an error and w edon't have an returntatement created so default one for progeram
    EXPECT_EQ(std::get<int>(programResult), 0);

    // Assuming 'env' is updated after executing the Program
    // Check the value of 'x' in the environment
    auto result = env.get("x");
    EXPECT_EQ(std::get<int>(result), 10); // Should be 10 as the 'then' block was executed
}

TEST(IfStatementTest, IfStatementElseBodyTest) {
    // Create an environment
    Env env;

    // Create a condition (e.g., true)
    std::unique_ptr<Expression> condition = std::make_unique<Bool>(false);

    // Create 'then' block (e.g., x = 10)
    std::list<std::unique_ptr<Statement>> thenBody;
    thenBody.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Integer>(10)));

    // Create 'else' block (e.g., x = 20), not executed in this test
    std::unique_ptr<Statement> elseBody = std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Integer>(20));

    // Create the IfStatement
    auto ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(thenBody), std::move(elseBody));

    // Create a Program containing the IfStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(ifStatement));

    Program program(std::move(programBody));

    // Create an Executor and execute the program
    Executor executor(env);
    Value programResult = executor.execute(program);
    // Check if the return is 0 like c++, beacuse the program is executed without an error and w edon't have an returntatement created so default one for progeram
    EXPECT_EQ(std::get<int>(programResult), 0);

    // Assuming 'env' is updated after executing the Program
    // Check the value of 'x' in the environment
    auto result = env.get("x");
    EXPECT_EQ(std::get<int>(result), 20); // Should be 10 as the 'then' block was executed
}

TEST(IfStatementTest, IfStatementNoElseBodyTest) {
    // Create an environment
    Env env;

    // Create a condition (e.g., true)
    std::unique_ptr<Expression> condition = std::make_unique<Bool>(false);

    // Create 'then' block (e.g., x = 10)
    std::list<std::unique_ptr<Statement>> thenBody;
    thenBody.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Integer>(10)));

    // Create the IfStatement
    auto ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(thenBody));

    // Create a Program containing the IfStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(ifStatement));

    Program program(std::move(programBody));

    // Create an Executor and execute the program
    Executor executor(env);
    Value programResult = executor.execute(program);
    // Check if the return is 0 like c++, beacuse the program is executed without an error and w edon't have an returntatement created so default one for progeram
    EXPECT_EQ(std::get<int>(programResult), 0);

    // Assuming 'env' is not updated after executing the Program since the 'else' block is not executed
}

TEST(IfStatementTest, IfStatementWithReturn) {
    // Create an environment
    Env env;

    // Create an assignment statement: x = 5
    auto assignment = std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<Integer>(5));

    // Create condition for the if statement: x < 5
    auto condition = std::make_unique<BinaryExpression>(
            std::make_unique<Identifier>("x"),
            std::make_unique<Integer>(5),
            "<"
    );

    // Create return statement for 'then' block: return "smaller"
    std::list<std::unique_ptr<Statement>> thenBody;
    thenBody.push_back(std::make_unique<ReturnStatement>(std::make_unique<String>("smaller")));

    // Create return statement for 'else' block: return "bigger"
    auto elseBody = std::make_unique<ReturnStatement>(std::make_unique<String>("bigger or equal"));

    // Create the IfStatement
    auto ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(thenBody), std::move(elseBody));

    // Create a Program containing the Assignment and IfStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(assignment));
    programBody.push_back(std::move(ifStatement));

    Program program(std::move(programBody));

    // Create an Executor and execute the program
    Executor executor(env);
    auto result = executor.execute(program);

    // Check the result of the program
    EXPECT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "bigger or equal"); // Since x is not less than 5, it should return "bigger"
}

TEST(IfStatementTest, IfStatementComplexConditionTest) {
    // Create an environment
    Env env;

    // Create a complex condition (e.g., (5 + 3) > 7)
    std::unique_ptr<Expression> condition = std::make_unique<BinaryExpression>(
            std::make_unique<BinaryExpression>(
                    std::make_unique<Integer>(5),
                    std::make_unique<Integer>(3),
                    "+"
            ),
            std::make_unique<Integer>(7),
            ">"
    );

    // Create 'then' block (e.g., x = "true")
    std::list<std::unique_ptr<Statement>> thenBody;
    thenBody.push_back(std::make_unique<AssignmentStatement>(Identifier("x"), std::make_unique<String>("true")));

    // Create the IfStatement without an 'else' body
    auto ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(thenBody));

    // Create a Program containing the IfStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(ifStatement));

    Program program(std::move(programBody));

    // Execute the program
    Executor executor(env);
    executor.execute(program);

    // Check the value of 'x' in the environment
    auto result = env.get("x");
    EXPECT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "true");
}
