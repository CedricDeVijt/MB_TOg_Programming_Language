#include "gtest/gtest.h"
#include "modules/Lexer.h"
#include "datatypes/CFG.h"

//TEST(parserTest, emptyTest) {
//    Tokens tokens;
//    Program result = Parser::parse(tokens, "...");
//    EXPECT_TRUE(result.getBody().empty());
//}
//
//TEST(parserTest, simpleTest) {
//    Tokens tokens = Lexer::lex("1 + 2");
//    Program result = Parser::parse(tokens, "...");
//    EXPECT_EQ(result.getBody().size(), 1);
//    EXPECT_EQ(result.getBody().front().getKind(), NodeType::BinaryExpression);
//}