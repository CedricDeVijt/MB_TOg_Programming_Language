#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <stack>
#include <variant>
#include <vector>
#include <memory>
#include "../datatypes/CFG.h"
#include "../datatypes/AST.h"
#include "../datatypes/Token.h"

using StackElement = std::variant<Token, std::shared_ptr<Statement>, std::shared_ptr<Program>, std::list<std::shared_ptr<Statement>>, int>;

class Parser {
public:
    Program parse(const Tokens &tokens, const std::string &parserTablePath);

private:
    std::shared_ptr<Statement> reduce (const std::pair<std::string, std::vector<std::string>> &rule, std::stack<StackElement> &parsingStack);

    int getStackTop(std::stack<StackElement> &parsingStack);

    std::string getNextToken(const Tokens &remainingTokens);
};

#endif