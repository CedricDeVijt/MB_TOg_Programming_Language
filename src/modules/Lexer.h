#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include "../datatypes/Token.h"
#include <regex>
using namespace std;

class Lexer{
public:
    static Tokens lex(const std::string &input);
};

#endif