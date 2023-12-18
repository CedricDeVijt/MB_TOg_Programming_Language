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

std::string Token::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::VAR: return "VAR";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::EQUALS: return "EQUALS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::COMMA: return "COMMA";
        case TokenType::OPENPAREN: return "OPENPAREN";
        case TokenType::CLOSEPAREN: return "CLOSEPAREN";
        case TokenType::INTEGER: return "INTEGER";
        case TokenType::PLUS: return "PLUS";
        case TokenType::TIMES: return "TIMES";
        case TokenType::DIVIDE: return "DIVIDE";
        default: return "UNKNOWN";
    }
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "value: " << token.value << std::endl << "tokenType: " << Token::tokenTypeToString(token.tokenType) <<std::endl<< "line: " << token.line << ", column: " << token.column << std::endl;
    return os;
}