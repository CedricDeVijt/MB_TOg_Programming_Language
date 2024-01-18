#ifndef OURLANG_PARSERTABLELOADER_H
#define OURLANG_PARSERTABLELOADER_H

#include <string>
#include <map>
#include "modules/Parser.h"

class ParserTableLoader {
public:
    static ParsingTable getParserTable(const std::string &path);

private:
    static TokenType getTokenType(const std::string &token);
    static ActionType getActionType(const std::string &actionType);
};


#endif //OURLANG_PARSERTABLELOADER_H
