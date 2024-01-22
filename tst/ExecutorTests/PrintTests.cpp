//
// Created by Siebe Mees on 17/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

class PrintTest : public ::testing::Test {
protected:
    std::streambuf* originalCoutStreamBuf;
    std::ostringstream capturedCout;

    void SetUp() override {
        // Redirect cout to our stringstream
        originalCoutStreamBuf = std::cout.rdbuf();
        std::cout.rdbuf(capturedCout.rdbuf());
    }

    void TearDown() override {
        // Restore the original stream buffer
        std::cout.rdbuf(originalCoutStreamBuf);
    }
};

TEST_F(PrintTest, BasicPrintTest) {
    // Create an environment
    Env env;

    // Create an executor
    Executor executor(env);

    // Creating a program with a simple print statement: print(5.8)
    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<PrintStatement>(std::make_unique<Float>(5.8)));
    Program program(std::move(statements));

    // Execute the program
    auto result = executor.execute(program);

    // Check if the return is 0 like c++
    EXPECT_EQ(std::get<int>(result), 0);

    // Check the captured output
    EXPECT_EQ(capturedCout.str(), "5.8\n");
}

TEST_F(PrintTest, StringPrintTest) {
    Env env;
    Executor executor(env);

    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<PrintStatement>(std::make_unique<String>("Hello, world!")));
    Program program(std::move(statements));

    executor.execute(program);
    EXPECT_EQ(capturedCout.str(), "Hello, world!\n");
}

TEST_F(PrintTest, IntegerPrintTest) {
    Env env;
    Executor executor(env);

    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<PrintStatement>(std::make_unique<Integer>(42)));
    Program program(std::move(statements));

    executor.execute(program);
    EXPECT_EQ(capturedCout.str(), "42\n");
}

TEST_F(PrintTest, BooleanPrintTest) {
    Env env;
    Executor executor(env);

    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<PrintStatement>(std::make_unique<Bool>(true)));
    Program program(std::move(statements));

    executor.execute(program);
    EXPECT_EQ(capturedCout.str(), "true\n");
}

TEST_F(PrintTest, MultipleStatementsPrintTest) {
    Env env;
    Executor executor(env);

    std::list<std::unique_ptr<Statement>> statements;
    statements.push_back(std::make_unique<PrintStatement>(std::make_unique<String>("First line")));
    statements.push_back(std::make_unique<PrintStatement>(std::make_unique<String>("Second line")));
    Program program(std::move(statements));

    executor.execute(program);
    EXPECT_EQ(capturedCout.str(), "First line\nSecond line\n");
}