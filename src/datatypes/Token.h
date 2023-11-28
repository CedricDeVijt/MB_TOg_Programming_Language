#ifndef MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H
#define MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H

#include <list>
#include <string>

enum class TokenType {
    Identifier,
    Var,
    If,
    Else,
    Function,
    While,
    OpenParen,
    CloseParen,
    Equals,
    Plus,
    Minus,
    Divide,
    Times,
    EOF
};

class Token {
public:
    Token(const std::string value = "", TokenType tokenType, int line, int column) = default;

private:
    std::string value;
    TokenType tokenType;
    int line;
    int column;
};

typedef std::list<Token> Tokens;

#endif //MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H