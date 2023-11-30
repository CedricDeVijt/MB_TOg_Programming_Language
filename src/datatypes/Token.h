#ifndef MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H
#define MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H

#include <list>
#include <string>

enum class TokenType {
    IDENTIFIER,
    VAR,
    If,
    Else,
    Function,
    While,
    OpenParen,
    CloseParen,
    EQUALS,
    Comma,
    Plus,
    Minus,
    Divide,
    Times,
    EOFTOKEN,
    INTEGER,
    String
};

class Token {
public:
    Token(TokenType tokenType, int line, int column, const std::string &value = "");

private:
    std::string value;
    TokenType tokenType;
    int line;
    int column;
};

typedef std::list<Token> Tokens;

#endif //MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H