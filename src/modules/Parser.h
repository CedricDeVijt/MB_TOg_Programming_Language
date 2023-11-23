#ifndef PARSER_H
#define PARSER_H

#include "../datatypes/CFG.h"
#include "../datatypes/AST.h"
#include "../datatypes/Token.h"

class Parser
{
public:
    static AST parse(const Tokens &tokens, const CFG &cfg);
};

#endif