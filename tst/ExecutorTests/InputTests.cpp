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

};

TEST_F(InputTest, BasicInputTest) {
    setTestInput("Test input string\n");

    // Create shared pointers for the stream
    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());

    // Create an environment with the modified cin
    Env env(nullptr, sharedCin, nullptr, nullptr);  // nullptrs are for stdout and stderr

    Value value = env.input();  // Assuming input() returns a Value
    ASSERT_EQ(std::get<std::string>(value), "Test input string");
}

TEST_F(InputTest, NumericInput) {
    setTestInput("12345\n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    Value value = env.input();
    ASSERT_EQ(std::get<std::string>(value), "12345");
}

TEST_F(InputTest, EmptyInput) {
    setTestInput("\n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    Value value = env.input();
    ASSERT_TRUE(std::get<std::string>(value).empty());
}

TEST_F(InputTest, MultipleLinesInput) {
    setTestInput("First line\nSecond line\n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    Value firstValue = env.input();
    Value secondValue = env.input();

    ASSERT_EQ(std::get<std::string>(firstValue), "First line");
    ASSERT_EQ(std::get<std::string>(secondValue), "Second line");
}

TEST_F(InputTest, InputWithLeadingAndTrailingSpaces) {
    setTestInput("  Hello World  \n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    Value value = env.input();
    ASSERT_EQ(std::get<std::string>(value), "  Hello World  ");
}

TEST_F(InputTest, InputWithSpecialCharacters) {
    setTestInput("!@# $%^ &*()\n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    Value value = env.input();
    ASSERT_EQ(std::get<std::string>(value), "!@# $%^ &*()");
}

TEST_F(InputTest, MultipleConsecutiveInputs) {
    setTestInput("First\nSecond\nThird\n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    ASSERT_EQ(std::get<std::string>(env.input()), "First");
    ASSERT_EQ(std::get<std::string>(env.input()), "Second");
    ASSERT_EQ(std::get<std::string>(env.input()), "Third");
}

TEST_F(InputTest, InputLargeText) {
    std::string largeText(1000, 'a');  // String of 1000 'a' characters
    setTestInput(largeText + "\n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    Value value = env.input();
    ASSERT_EQ(std::get<std::string>(value), largeText);
}

TEST_F(InputTest, InputNumericString) {
    setTestInput("1234567890\n");

    auto sharedCin = std::make_shared<std::istream>(testInput.rdbuf());
    Env env(nullptr, sharedCin, nullptr, nullptr);

    Value value = env.input();
    ASSERT_EQ(std::get<std::string>(value), "1234567890");
}