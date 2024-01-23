//
// Created by Siebe Mees on 11/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"

TEST(EnvironmentTest, InheritFromParent) {
    Env parent;
    parent.set("parentKey", "parentValue");

    Env child(&parent);
    Value value = child.get("parentKey");
    ASSERT_EQ(std::get<std::string>(value), "parentValue");
}

TEST(EnvironmentTest, OverrideParentValue) {
    Env parent;
    parent.set("key", "parentValue");

    Env child(&parent);
    child.set("key", "childValue");

    Value childValue = child.get("key");
    ASSERT_EQ(std::get<std::string>(childValue), "childValue");
    Value parentValue = parent.get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");
}

TEST(EnvironmentTest, NonExistentKey) {
    Env env;
    EXPECT_THROW({Value value = env.get("nonExistentKey");}, std::runtime_error);
}

TEST(EnvironmentTest, NonExistentKeyCatchError) {
    Env env;

    try {
        Value value = env.get("nonExistentKey");
        // If no exception is thrown, fail the test
        FAIL() << "Expected std::runtime_error";
    } catch (const std::runtime_error& err) {
        // Check that the error message is what we expect
        EXPECT_EQ(err.what(), std::string("Variable not found: nonExistentKey"));
    } catch (...) {
        // If any other exception is thrown, fail the test
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(EnvironmentTest, CheckKeyExistence) {
    Env env;
    env.set("existingKey", "value");

    ASSERT_TRUE(env.contains("existingKey"));
    ASSERT_FALSE(env.contains("nonExistentKey"));
}

TEST(EnvironmentTest, StringRepresentation) {
    Env env;
    env.set("key1", "value1");
    env.set("key2", "value2");

    Value representation = env.toString();

    ASSERT_NE(std::get<std::string>(representation).find("key1=value1"), std::string::npos);
    ASSERT_NE(std::get<std::string>(representation).find("key2=value2"), std::string::npos);
}

TEST(EnvironmentTest, ScopeShadowing) {
    Env parent;
    parent.set("key", "parentValue");

    Env child(&parent);
    child.set("key", "childValue");

    Value childValue = child.get("key");
    ASSERT_EQ(std::get<std::string>(childValue), "childValue");

    Value parentValue = parent.get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");
}

TEST(EnvironmentTest, InheritedVariables) {
    Env parent;
    parent.set("parentKey", "parentValue");

    Env child(&parent);
    Value childValue = child.get("parentKey");
    ASSERT_EQ(std::get<std::string>(childValue), "parentValue");
}

TEST(EnvironmentTest, SeparateScopes) {
    Env parent;
    parent.set("key", "parentValue");

    Env child(&parent);
    child.set("key", "childValue");

    // Modifying child should not affect parent
    child.set("key", "newValue");

    Value parentValue = parent.get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");
}

TEST(EnvironmentTest, NestedScopes) {
    Env grandparent;
    grandparent.set("key", "grandparentValue");

    Env parent(&grandparent);
    parent.set("key", "parentValue");

    Env child(&parent);

    Value grandparentValue = grandparent.get("key");
    ASSERT_EQ(std::get<std::string>(grandparentValue), "grandparentValue");

    Value parentValue = parent.get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");

    Value childValue = child.get("key");
    ASSERT_EQ(std::get<std::string>(childValue), "parentValue"); // Inherits from parent
}

TEST(EnvironmentTest, VariableSetInInnerScope) {
    Env outerEnv;

    {
        Env innerEnv(&outerEnv);
        innerEnv.set("a", Value(5));  // Set 'a' in the inner environment
    }  // 'a' goes out of scope here

    // Trying to access 'a' in the outer environment should fail or return a default value
    // Error: "Variable not found: a"
    EXPECT_THROW({ outerEnv.get("a"); }, std::runtime_error);
}

TEST(EnvironmentTest, VariableShadowingAndAccess) {
    Env outerEnv;
    outerEnv.set("a", Value(10));  // Set 'a' in the outer environment

    {
        Env innerEnv(&outerEnv);
        innerEnv.set("a", Value(5));  // Shadow 'a' in the inner environment
    }  // Inner 'a' goes out of scope here

    // Accessing 'a' in the outer environment should yield the original value
    Value aValue = outerEnv.get("a");
    ASSERT_EQ(std::get<int>(aValue), 10);
}