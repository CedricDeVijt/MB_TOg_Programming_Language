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
        case TokenType::BOOL: return "BOOL";
        case TokenType::LESSTHAN: return "LESSTHAN";
        case TokenType::GREATHERTHAN: return "GREATHERTHAN";
        case TokenType::IF: return "IF LOOP";
        case TokenType::ELSEIF: return "ELSE IF LOOP";
        case TokenType::ELSE: return "ELSE LOOP";
        case TokenType::WHILE: return "WHILE LOOP";
        case TokenType::FUNCTION: return "FUNCTIE";
            //case TokenType::FUNCTIONNAME: return "FUNCTIE NAAM";
        case TokenType::FOR: return "FOR LOOP";
        case TokenType::PRINT: return "PRINT";
        case TokenType::USERINPUT: return "ASK FOR USER INPUT";
        case TokenType::INPUT: return "INPUT FROM USER";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::FLOAT: return "FLOAT";
        case TokenType::LIMIT: return "LIMIT";
        case TokenType::STRING: return "STRING";
        case TokenType::EOFTOKEN: return "END OF FILE";
        case TokenType::OPENBODY: return "START OF STATEMENT";
        case TokenType::CLOSEBODY: return "END OF STATEMENT";
        case TokenType::RETURN: return "RETURN";


        default: return "UNKNOWN";
    }
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "value: " << token.value << std::endl << "tokenType: " << Token::tokenTypeToString(token.tokenType) <<std::endl<< "line: " << token.line << ", column: " << token.column << std::endl;
    return os;
}

const std::string &Token::getValue() const {
    return value;
}

TokenType Token::getTokenType() const {
    return tokenType;
}
