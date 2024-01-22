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