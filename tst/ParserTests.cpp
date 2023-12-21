#include "gtest/gtest.h"
#include "modules/Parser.h"
#include "modules/Lexer.h"

TEST(parserTest, emptyTest) {
    Tokens tokens;
    Program result = Parser::parse(tokens, CFG("src/cfg.json"));
    EXPECT_TRUE(result.getBody().empty());
}

TEST(parserTest, simpleTest) {
    Tokens tokens = Lexer::lex("1 + 2");
    Program result = Parser::parse(tokens, CFG("src/cfg.json"));
    EXPECT_EQ(result.getBody().size(), 1);
    EXPECT_EQ(result.getBody().front().getKind(), NodeType::BinaryExpression);
}

//TEST(parserTest, complexTest) {
//    Tokens tokens = Lexer::lex("1 + 2 * 3");
//    Program result = Parser::parse(tokens, CFG("src/cfg.json"));
//    EXPECT_EQ(result.getBody().size(), 1);
//    EXPECT_EQ(result.getBody().front().getKind(), NodeType::BinaryExpression);
//    const BinaryExpression &binExp = (const BinaryExpression &) result.getBody().front();
//    EXPECT_EQ(binExp.getLeft().getKind(), NodeType::Float);
//    EXPECT_EQ(binExp.getRight().getKind(), NodeType::BinaryExpression);
//    const BinaryExpression &binExp2 = (const BinaryExpression &) binExp.getRight();
//    EXPECT_EQ(binExp2.getLeft().getKind(), NodeType::Float);
//    EXPECT_EQ(binExp2.getRight().getKind(), NodeType::Float);
//}