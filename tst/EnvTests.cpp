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
    Value value = env.get("nonExistentKey");
    ASSERT_TRUE(value.index() != 0);
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