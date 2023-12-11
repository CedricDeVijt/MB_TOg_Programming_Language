//
// Created by Siebe Mees on 11/12/2023.
//
#include "gtest/gtest.h"
#include "../src/modules/executionEnvironment/Environment.h"

TEST(EnvironmentTest, InheritFromParent) {
    Env parent;
    parent.set("parentKey", "parentValue");

    Env child(&parent);
    std::string value = child.get("parentKey");
    ASSERT_EQ(value, "parentValue");
}

TEST(EnvironmentTest, OverrideParentValue) {
    Env parent;
    parent.set("key", "parentValue");

    Env child(&parent);
    child.set("key", "childValue");

    ASSERT_EQ(child.get("key"), "childValue");
    ASSERT_EQ(parent.get("key"), "parentValue");
}

TEST(EnvironmentTest, NonExistentKey) {
    Env env;
    std::string value = env.get("nonExistentKey");
    ASSERT_TRUE(value.empty());
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