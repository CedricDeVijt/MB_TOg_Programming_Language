//
// Created by Siebe Mees on 17/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

class InputTest : public ::testing::Test {
protected:
    std::streambuf* originalCinStreamBuf;
    std::istringstream testInput;

    void SetUp() override {
        // Save the original cin stream buffer
        originalCinStreamBuf = std::cin.rdbuf();

        // Redirect cin to our input stream
        std::cin.rdbuf(testInput.rdbuf());
    }

    void TearDown() override {
        // Restore the original cin stream buffer
        std::cin.rdbuf(originalCinStreamBuf);
    }

    void setTestInput(const std::string& input) {
        testInput = std::istringstream(input);
    }

    std::string variantToString(const std::variant<float, int, std::string, bool>& var) {
        std::ostringstream ss;
        std::visit([&ss](auto&& arg) {
            ss << arg;
        }, var);
        return ss.str();
    }
};

TEST_F(InputTest, BasicInputTest) {
    // Set the test input
    setTestInput("some input value\n");

    // Create an environment
    Env env;

    // Create an InputStatement
    InputStatement inputStmt("variableName");

    // Execute the InputStatement
    inputStmt.execute(env);

    // Retrieve the value from the environment and verify
    auto value = env.get("variableName");
    EXPECT_EQ(variantToString(value), "some input value");
}

TEST_F(InputTest, SingleWordInputTest) {
    setTestInput("word\n");

    Env env;
    InputStatement inputStmt("variableName");
    inputStmt.execute(env);

    auto value = env.get("variableName");
    EXPECT_EQ(variantToString(value), "word");
}

TEST_F(InputTest, NumericInputTest) {
    setTestInput("12345\n");

    Env env;
    InputStatement inputStmt("numericVariable");
    inputStmt.execute(env);

    auto value = env.get("numericVariable");
    EXPECT_EQ(variantToString(value), "12345");
}

TEST_F(InputTest, EmptyInputTest) {
    setTestInput("\n");

    Env env;
    InputStatement inputStmt("emptyVariable");
    inputStmt.execute(env);

    auto value = env.get("emptyVariable");
    EXPECT_EQ(variantToString(value), "");
}

TEST_F(InputTest, SpecialCharacterInputTest) {
    setTestInput("!@#$%^&*()\n");

    Env env;
    InputStatement inputStmt("specialCharVariable");
    inputStmt.execute(env);

    auto value = env.get("specialCharVariable");
    EXPECT_EQ(variantToString(value), "!@#$%^&*()");
}