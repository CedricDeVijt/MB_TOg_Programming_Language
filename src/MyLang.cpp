#include "MyLang.h"

#include <memory>


void MyLang::interpret(const std::string &input, const std::string &parserTablePath) {
    // Lexer
    Tokens tokens = Lexer::lex(input);
    // Parser
    Parser parser;
    Program program = parser.parse(tokens, parserTablePath);
    // Executor
    Env env(nullptr, std::cin, std::cout, std::cerr);
    Executor executor(env);
    executor.execute(program);
}


