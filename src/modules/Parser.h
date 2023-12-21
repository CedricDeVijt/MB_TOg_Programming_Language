#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <stack>
#include "../datatypes/CFG.h"
#include "../datatypes/AST.h"
#include "../datatypes/Token.h"

using StackElement = int;

enum ActionType {
    SHIFT, REDUCE, GOTO, ACCEPT, ERROR
};

struct TableEntry {
    ActionType actionType;
    StackElement state;
};

using ParsingTable = std::map<std::pair<int, char>, TableEntry>;

class Parser {
private:
    ParsingTable parsingTable;
    std::stack<StackElement> parsingStack;
public:
    static Program parse(const Tokens &tokens, const CFG &cfg);

private:
    void initializeParsingTable();
};

#endif