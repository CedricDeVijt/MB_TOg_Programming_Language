#ifndef LEXER_H
#define LEXER_H


#include<iostream>
#include <regex>
#include "../datatypes/Token.h"
using namespace std;





class Lexer{

public:
    static Tokens lex(const std::string &input);
};

#endif