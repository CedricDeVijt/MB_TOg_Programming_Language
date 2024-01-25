#include "MyLang.h"
#include <memory>

MyLang::MyLang(const CFG &cfg) : cfg(cfg) {}

void MyLang::interpret(const std::string &input) {
    // Lexer
    Tokens tokens = Lexer::lex(input);
    // Parser
    Parser parser;
    Program program = parser.parse(tokens, "../../data/LRParserTable.json");
    // Executor
    Env env(nullptr, std::cin, std::cout, std::cerr);
    Executor executor(env);
    executor.execute(program);
}


