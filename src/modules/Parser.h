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

using StackElement = std::variant<Token, Statement, int>;

class Parser {
public:
    Program parse(const Tokens &tokens, const std::string &parserTablePath);

private:
    std::unique_ptr<Statement> reduce (const std::pair<std::string, std::vector<std::string>> &rule, std::stack<StackElement> &parsingStack);
};

#endif