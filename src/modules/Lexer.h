#ifndef LEXER_H
#define LEXER_H

#include "../datatypes/Token.h"

class Lexer
{
public:
    static Tokens lex(const std::string &input);
};

#endif