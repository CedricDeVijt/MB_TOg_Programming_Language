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
        case TokenType::VAR: return "var";
        case TokenType::IDENTIFIER: return "identifier";
        case TokenType::EQUALS: return "equals";
        case TokenType::MINUS: return "-";
        case TokenType::COMMA: return "comma";
        case TokenType::OPENPAREN: return "openparan";
        case TokenType::CLOSEPAREN: return "closeparan";
        case TokenType::INTEGER: return "float";
        case TokenType::PLUS: return "+";
        case TokenType::TIMES: return "*";
        case TokenType::DIVIDE: return "/";
        case TokenType::BOOL: return "bool";
        /*case TokenType::LESSTHAN: return "<";
        case TokenType::GREATHERTHAN: return ">";*/
        case TokenType::IF: return "if";
        //case TokenType::ELSEIF: return "elseif";
        case TokenType::ELSE: return "else";
        case TokenType::WHILE: return "while";
        case TokenType::FUNCTION: return "function";
        //case TokenType::FUNCTIONNAME: return "FUNCTIE NAAM";
        //case TokenType::FOR: return "FOR LOOP";
        //case TokenType::PRINT: return "PRINT";
        //case TokenType::USERINPUT: return "ASK FOR USER INPUT";
        //case TokenType::INPUT: return "INPUT FROM USER";
        //case TokenType::COMMENT: return "comment";
        case TokenType::FLOAT: return "float";
        //case TokenType::LIMIT: return "LIMIT";
        case TokenType::STRING: return "string";
        case TokenType::EOFTOKEN: return "eof";
        case TokenType::OPENBODY: return "bodyopen";
        case TokenType::CLOSEBODY: return "bodyclose";
        case TokenType::RETURN: return "return";


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
