#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <stack>
#include <variant>
#include "../datatypes/CFG.h"
#include "../datatypes/AST.h"
#include "../datatypes/Token.h"

using StackElement =  std::variant<Token, Statement,int>;

class Parser {
public:
    static Program parse(const Tokens &tokens, const std::string& parserTablePath);
};

#endif