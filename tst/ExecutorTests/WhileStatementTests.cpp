//
// Created by Siebe Mees on 21/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

TEST(WhileStatementTest, BasicWhileStatement) {
    // Create an environment
    Env env;

    // Create an executor
    Executor executor(env);

    // Create a variable and initialize it to 0
    env.set("counter", Value(0));

    // Create a condition for the while statement: counter < 5
    auto condition = std::make_unique<BinaryExpression>(
            std::make_unique<Identifier>("counter"),
            std::make_unique<Integer>(5),
            "<"
    );

    // Create the body of the while loop: counter = counter + 1
    std::list<std::unique_ptr<Statement>> body;
    body.push_back(std::make_unique<AssignmentStatement>(
            Identifier("counter"),
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("counter"),
                    std::make_unique<Integer>(1),
                    "+"
            )
    ));

    // Create the WhileStatement
    auto whileStatement = std::make_unique<WhileStatement>(std::move(condition), std::move(body));

    // Create a Program containing the WhileStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(whileStatement));

    Program program(std::move(programBody));

    // Execute the program
    executor.execute(program);

    // Retrieve the value of 'counter' from the environment
    Value counterValue = env.get("counter");

    // Check if the counter has the expected value (5)
    EXPECT_EQ(std::get<int>(counterValue), 5);
}

TEST(WhileStatementTest, WhileWithMultipleStatements) {
    Env env;
    Executor executor(env);

    // Initialize two variables
    env.set("a", Value(0));
    env.set("sum", Value(0));

    // Condition: a < 10
    auto condition = std::make_unique<BinaryExpression>(
            std::make_unique<Identifier>("a"),
            std::make_unique<Integer>(10),
            "<"
    );

    // Body: Increment 'a' and add 'a' to 'sum'
    std::list<std::unique_ptr<Statement>> body;
    body.push_back(std::make_unique<AssignmentStatement>(
            Identifier("a"),
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("a"),
                    std::make_unique<Integer>(1),
                    "+"
            )
    ));
    body.push_back(std::make_unique<AssignmentStatement>(
            Identifier("sum"),
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("sum"),
                    std::make_unique<Identifier>("a"),
                    "+"
            )
    ));

    // WhileStatement
    auto whileStatement = std::make_unique<WhileStatement>(std::move(condition), std::move(body));

    // Create a Program containing the whilestatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(whileStatement));
    Program program(std::move(programBody));

    // Execute
    executor.execute(program);

    // Check final values
    EXPECT_EQ(std::get<int>(env.get("a")), 10);
    EXPECT_EQ(std::get<int>(env.get("sum")), 55); // Sum of numbers 0 to 9
}

TEST(WhileStatementTest, WhileLoopWithVariableInitializationAndModification) {
    Env env;
    Executor executor(env);

    // Initialize a variable
    env.set("num", Value(0));

    // Condition: num < 3
    auto condition = std::make_unique<BinaryExpression>(
            std::make_unique<Identifier>("num"),
            std::make_unique<Integer>(3),
            "<"
    );

    // Loop body: increment 'num'
    std::list<std::unique_ptr<Statement>> body;
    body.push_back(std::make_unique<AssignmentStatement>(
            Identifier("num"),
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("num"),
                    std::make_unique<Integer>(1),
                    "+"
            )
    ));

    // Create WhileStatement
    auto whileStatement = std::make_unique<WhileStatement>(std::move(condition), std::move(body));

    // Create a Program containing the WhileStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(whileStatement));
    Program program(std::move(programBody));

    // Execute the program
    executor.execute(program);

    // Check if 'num' reached the expected value (3)
    EXPECT_EQ(std::get<int>(env.get("num")), 3);
}

TEST(WhileStatementTest, WhileLoopWithInnerIfElse) {
    Env env;
    Executor executor(env);

    // Initialize variables
    env.set("i", Value(1));
    env.set("evenSum", Value(0));
    env.set("oddSum", Value(0));

    // Condition: i <= 10
    auto condition = std::make_unique<BinaryExpression>(
            std::make_unique<Identifier>("i"),
            std::make_unique<Integer>(10),
            "<="
    );

    // Loop body: sum even and odd numbers separately
    std::list<std::unique_ptr<Statement>> ifThenBody;
    ifThenBody.push_back(std::make_unique<AssignmentStatement>(
            Identifier("evenSum"),
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("evenSum"),
                    std::make_unique<Identifier>("i"),
                    "+"
            )
    ));

    auto elseBody = std::make_unique<AssignmentStatement>(
            Identifier("oddSum"),
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("oddSum"),
                    std::make_unique<Identifier>("i"),
                    "+"
            )
    );

    std::list<std::unique_ptr<Statement>> body;
    body.push_back(std::make_unique<IfStatement>(
            std::make_unique<BinaryExpression>(
                    std::make_unique<BinaryExpression>(
                            std::make_unique<Identifier>("i"),
                            std::make_unique<Integer>(2),
                            "%"
                    ),
                    std::make_unique<Integer>(0),
                    "=="
            ),
            std::move(ifThenBody),
            std::move(elseBody)
    ));
    body.push_back(std::make_unique<AssignmentStatement>(
            Identifier("i"),
            std::make_unique<BinaryExpression>(
                    std::make_unique<Identifier>("i"),
                    std::make_unique<Integer>(1),
                    "+"
            )
    ));

    // Create WhileStatement
    auto whileStatement = std::make_unique<WhileStatement>(std::move(condition), std::move(body));

    // Create a Program containing the WhileStatement
    std::list<std::unique_ptr<Statement>> programBody;
    programBody.push_back(std::move(whileStatement));
    Program program(std::move(programBody));

    // Execute the program
    executor.execute(program);

    // Check final values
    EXPECT_EQ(std::get<int>(env.get("evenSum")), 30); // Sum of even numbers 2, 4, 6, 8, 10
    EXPECT_EQ(std::get<int>(env.get("oddSum")), 25);  // Sum of odd numbers 1, 3, 5, 7, 9
}
