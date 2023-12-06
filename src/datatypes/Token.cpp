#include "Token.h"

Token::Token(TokenType tokenType, int line, int column, const std::string &value)
: tokenType(tokenType), line(line), column(column), value(value) {}

bool Token::operator==(const Token &rhs) const {
    return value == rhs.value &&
           tokenType == rhs.tokenType &&
           line == rhs.line &&
           column == rhs.column;
}

bool Token::operator!=(const Token &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "value: " << token.value << " tokenType: " << static_cast<int>(token.tokenType) << " line: " << token.line << " column: " << token.column;
    return os;
}