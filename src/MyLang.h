#ifndef MB_TOG_PROGRAMMING_LANGUAGE_MYLANG_H
#define MB_TOG_PROGRAMMING_LANGUAGE_MYLANG_H

#include "./modules/Lexer.h"
#include "./modules/Executor.h"
#include "./modules/Parser.h"

class MyLang {
public:
    static void interpret(const std::string &input, const std::string &parserTablePath);
};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_MYLANG_H
