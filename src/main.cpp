#include "./modules/ASTGenerator.h"
#include "./modules/Lexer.h"
#include "./modules/Executor.h"

int main(int argc, char *argv[]) {
    ASTGenerator generator(ParsingTable("./data/table.json"));
    Tokens tokens = Lexer::lex("print(5)");
    Program p = generator.generate(tokens);
    Env env(nullptr, std::cin, std::cout, std::cerr);
    Executor executor(env);
    executor.execute(p);
    return 0;
}