//
// Created by Siebe Mees on 17/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"
#include "../src/modules/Executor.h"
#include "../src/datatypes/AST.h"

class PrintTest : public ::testing::Test {
protected:
    std::shared_ptr<std::ostream> sharedCout;
    std::ostringstream capturedCout;

    void SetUp() override {
        capturedCout.str(""); // Clear any existing content
        capturedCout.clear(); // Clear any error flags

        sharedCout = std::make_shared<std::ostream>(capturedCout.rdbuf());
    }

};

TEST_F(PrintTest, BasicPrintTest) {
    // Create an environment with capturedCout as stdout
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    // Simulate calling the print function with a string argument
    std::vector<Value> args = {"Hello, World!"};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "Hello, World!\n");  // Check the captured output
}

TEST_F(PrintTest, PrintMultipleDataTypes) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value(42), Value(" and "), Value(3.14f)};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "42 and 3.14\n");
}

TEST_F(PrintTest, PrintWithNoArguments) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args;  // Empty arguments

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "\n");
}

TEST_F(PrintTest, PrintBooleanValues) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value(true), Value(" is not "), Value(false)};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "true is not false\n");
}

TEST_F(PrintTest, PrintSpecialCharacters) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value("Special characters: "), Value("@#$%^&*")};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "Special characters: @#$%^&*\n");
}

TEST_F(PrintTest, PrintConcatenatedStrings) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value("Hello"), Value(", "), Value("World"), Value("!")};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "Hello, World!\n");
}

TEST_F(PrintTest, PrintComplexNestedExpressions) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {
            Value("Result: "), Value(42), Value(" - "), Value(3.14f), Value(" = "), Value(42 - 3.14f)
    };

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "Result: 42 - 3.14 = 38.86\n");
}

TEST_F(PrintTest, PrintLongString) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::string longString(1000, 'x');  // String with 1000 'x' characters
    std::vector<Value> args = {Value(longString)};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), longString + "\n");
}

TEST_F(PrintTest, PrintLineBreaks) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value("First Line\nSecond Line\nThird Line")};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "First Line\nSecond Line\nThird Line\n");
}

TEST_F(PrintTest, PrintMixedNumericalTypes) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value(123), Value(" + "), Value(4.56f), Value(" = "), Value(123 + 4.56f)};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "123 + 4.56 = 127.56\n");
}

TEST_F(PrintTest, PrintEmptyString) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value("")};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "\n");
}

TEST_F(PrintTest, RepeatedPrintCalls) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    env.print({Value("First Call")});
    env.print({Value("Second Call")});

    ASSERT_EQ(capturedCout.str(), "First Call\nSecond Call\n");
}

TEST_F(PrintTest, PrintEscapedCharacters) {
    Env env(nullptr, std::cin, capturedCout, std::cerr);  // Use global objects for stdin and stderr
    std::vector<Value> args = {Value("Tab:\t"), Value("Newline:\n"), Value("Backslash:\\")};

    env.print(args);
    ASSERT_EQ(capturedCout.str(), "Tab:\tNewline:\nBackslash:\\\n");
}