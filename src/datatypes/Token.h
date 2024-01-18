#ifndef MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H
#define MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H

#include <list>
#include <string>
#include <ostream>

enum class TokenType {
    IDENTIFIER,
    VAR,
    IF,
    ELSEIF,
    ELSE,
    WHILE,
    FOR,
    OPENPAREN,
    CLOSEPAREN,
    EQUALS,
    COMMA,
    PLUS,
    MINUS,
    DIVIDE,
    TIMES,
    EOFTOKEN,
    INTEGER,
    STRING,
    GREATHERTHAN,
    LESSTHAN,
    BOOL,
    FUNCTION,
    FUNCTIONNAME,
    PRINT,
    USERINPUT,
    INPUT,
    COMMENT,
    FLOAT,
    LIMIT
};


class Token {
public:
    Token(TokenType tokenType, int line, int column, const std::string &value = "");

    [[nodiscard]] TokenType getTokenType() const;

public:
    bool operator==(const Token &rhs) const;
    bool operator!=(const Token &rhs) const;
    static std::string tokenTypeToString(TokenType type);
    friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
    std::string value;
    TokenType tokenType;
    int line;
    int column;
};

typedef std::list<Token> Tokens;

#endif //MB_TOG_PROGRAMMING_LANGUAGE_TOKEN_H