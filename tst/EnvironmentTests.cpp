//
// Created by Siebe Mees on 11/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"

TEST(EnvironmentTest, InheritFromParent) {
    // Create a parent environment with nullptr streams
    auto parent = std::make_shared<Env>();
    parent->set("parentKey", "parentValue");

    // Create a child environment with the parent environment
    Env child(parent);
    Value value = child.get("parentKey");
    ASSERT_EQ(std::get<std::string>(value), "parentValue");
}

TEST(EnvironmentTest, OverrideParentValue) {
    auto parent = std::make_shared<Env>();
    parent->set("key", "parentValue");

    Env child(parent);
    child.set("key", "childValue");

    Value childValue = child.get("key");
    ASSERT_EQ(std::get<std::string>(childValue), "childValue");
    Value parentValue = parent->get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");
}


TEST(EnvironmentTest, NonExistentKey) {
    Env env;
    EXPECT_THROW({ env.get("nonExistentKey"); }, std::runtime_error);
}

TEST(EnvironmentTest, NonExistentKeyCatchError) {
    Env env;

    try {
        env.get("nonExistentKey");
        FAIL() << "Expected std::runtime_error";
    } catch (const std::runtime_error& err) {
        EXPECT_EQ(err.what(), std::string("Variable not found: nonExistentKey"));
    } catch (...) {
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

    std::string representation = env.toString();
    ASSERT_NE(representation.find("key1=value1"), std::string::npos);
    ASSERT_NE(representation.find("key2=value2"), std::string::npos);
}

TEST(EnvironmentTest, ScopeShadowing) {
    auto parent = std::make_shared<Env>();
    parent->set("key", "parentValue");

    Env child(parent);
    child.set("key", "childValue");

    Value childValue = child.get("key");
    ASSERT_EQ(std::get<std::string>(childValue), "childValue");

    Value parentValue = parent->get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");
}

TEST(EnvironmentTest, InheritedVariables) {
    auto parent = std::make_shared<Env>();
    parent->set("parentKey", "parentValue");

    Env child(parent);
    Value childValue = child.get("parentKey");
    ASSERT_EQ(std::get<std::string>(childValue), "parentValue");
}

TEST(EnvironmentTest, SeparateScopes) {
    auto parent = std::make_shared<Env>();
    parent->set("key", "parentValue");

    Env child(parent);
    child.set("key", "newValue");

    Value parentValue = parent->get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");
}

TEST(EnvironmentTest, NestedScopes) {
    auto grandparent = std::make_shared<Env>();
    grandparent->set("key", "grandparentValue");

    Env parent(grandparent);
    parent.set("key", "parentValue");

    Env child(parent);

    Value grandparentValue = grandparent->get("key");
    ASSERT_EQ(std::get<std::string>(grandparentValue), "grandparentValue");

    Value parentValue = parent.get("key");
    ASSERT_EQ(std::get<std::string>(parentValue), "parentValue");

    Value childValue = child.get("key");
    ASSERT_EQ(std::get<std::string>(childValue), "parentValue");
}


TEST(EnvironmentTest, VariableSetInInnerScope) {
    auto outerEnv = std::make_shared<Env>();

    {
        Env innerEnv(outerEnv);
        innerEnv.set("a", Value(5));  // Set 'a' in the inner environment
    }  // 'a' goes out of scope here

    // Trying to access 'a' in the outer environment should fail or return a default value
    // Error: "Variable not found: a"
    EXPECT_THROW({ outerEnv->get("a"); }, std::runtime_error);
}

TEST(EnvironmentTest, VariableShadowingAndAccess) {
    auto outerEnv = std::make_shared<Env>();
    outerEnv->set("a", Value(10));  // Set 'a' in the outer environment

    {
        Env innerEnv(outerEnv);
        innerEnv.set("a", Value(5));  // Shadow 'a' in the inner environment
    }  // Inner 'a' goes out of scope here

    // Accessing 'a' in the outer environment should yield the original value
    Value aValue = outerEnv->get("a");
    ASSERT_EQ(std::get<int>(aValue), 10);
}

TEST(EnvironmentTest, SetAndGetDifferentDataTypes) {
    Env env;
    env.set("intValue", Value(42));
    env.set("stringValue", Value("Hello"));
    env.set("floatValue", Value(3.14f));
    env.set("boolValue", Value(true));

    ASSERT_EQ(std::get<int>(env.get("intValue")), 42);
    ASSERT_EQ(std::get<std::string>(env.get("stringValue")), "Hello");
    ASSERT_EQ(std::get<float>(env.get("floatValue")), 3.14f);
    ASSERT_EQ(std::get<bool>(env.get("boolValue")), true);
}

TEST(EnvironmentTest, FunctionBindingAndExecution) {
    Env env;
    auto addFunction = [](const std::vector<Value>& args) -> Value {
        return std::get<int>(args[0]) + std::get<int>(args[1]);
    };
    env.setFunction("add", addFunction);

    // Assuming setFunction and executeFunction are implemented in Env
    std::vector<Value> arguments = {Value(5), Value(3)};
    Value result = env.executeFunction("add", arguments);

    ASSERT_EQ(std::get<int>(result), 8);
}

TEST(EnvironmentTest, ParentScopeDoesNotAccessChildScope) {
    auto parent = std::make_shared<Env>();

    {
        Env child(parent);
        child.set("childOnlyKey", Value("childValue"));
    }

    EXPECT_THROW({ parent->get("childOnlyKey"); }, std::runtime_error);
}

TEST(EnvironmentTest, RecursiveVariableLookup) {
    auto grandparent = std::make_shared<Env>();
    grandparent->set("key", "grandparentValue");

    Env parent(grandparent);
    Env child(parent);

    ASSERT_EQ(std::get<std::string>(child.get("key")), "grandparentValue");
}

TEST(EnvironmentTest, ModifyParentScopeVariableFromChild) {
    auto parent = std::make_shared<Env>();
    parent->set("key", "originalValue");

    {
        Env child(parent);
        child.set("key", "modifiedValue");
    }

    ASSERT_EQ(std::get<std::string>(parent->get("key")), "originalValue");
}

TEST(EnvironmentTest, MultipleChildrenModifySameParentVariable) {
    auto parent = std::make_shared<Env>();
    parent->set("key", "originalValue");

    {
        Env child1(parent);
        child1.set("key", "child1Value");
    }

    {
        Env child2(parent);
        child2.set("key", "child2Value");
    }

    ASSERT_EQ(std::get<std::string>(parent->get("key")), "originalValue");
}
