#include "Token.h"

Token::Token(TokenType tokenType, int line, int column, const std::string &value)
: tokenType(tokenType), line(line), column(column), value(value) {}
