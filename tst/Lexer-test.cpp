#include "gtest/gtest.h"
#include "modules/Lexer.h"

TEST(lexerTest, emtpyTest) {
    std::string in;
    Tokens tokens = Lexer::lex(in);
    EXPECT_TRUE(tokens.empty());
}

// TODO: dont fill obvious TokenType values
TEST(lexerTest, varTest) {
    std::string in = "var";
    Token iGot = *Lexer::lex(in).begin();
    Token expected = Token(TokenType::VAR, 0, 0);
    EXPECT_EQ(iGot, expected);
}

TEST(lexerTest, identifierTest1) {
    std::string in = "x";
    Token iGot = *Lexer::lex(in).begin();
    Token expected = Token(TokenType::IDENTIFIER, 0, 0, in);
    EXPECT_EQ(iGot, expected);
}

TEST(lexerTest, identifierTest2) {
    std::string in = "abooo12";
    Token iGot = *Lexer::lex(in).begin();
    Token expected = Token(TokenType::IDENTIFIER, 0, 0, in);
    EXPECT_EQ(iGot, expected);
}


// TODO: create custom exception so we can catch a syntax error.
//TEST(lexerTest, identifierTest2) {
//    std::string in = "123";
//    Token iGot = *Lexer::lex(in).begin();
//    Token expected = Token(TokenType::IDENTIFIER, 0, 0, in);
//    EXPECT_EQ(iGot, expected);
//}