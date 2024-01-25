#include "MyLang.h"

MyLang::MyLang(const CFG &cfg) : cfg(cfg) {}

void MyLang::interpret(const std::string &input) {
    Lexer::lex(input);
}


