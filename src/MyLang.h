#ifndef MB_TOG_PROGRAMMING_LANGUAGE_MYLANG_H
#define MB_TOG_PROGRAMMING_LANGUAGE_MYLANG_H

#include "./modules/Lexer.h"
#include "./modules/Executor.h"
#include "./modules/Parser.h"

class MyLang {
public:
    explicit MyLang(const CFG &cfg);

public:
    void interpret(const std::string &input);

private:
    CFG cfg;

};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_MYLANG_H
