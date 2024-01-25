#ifndef OURLANG_PARSINGTABLE_H
#define OURLANG_PARSINGTABLE_H

#include <string>
#include <map>
#include <variant>
#include <vector>

#include "../datatypes/Token.h"
#include "../datatypes/AST.h"

enum class ActionType {
    SHIFT,
    REDUCE,
    GOTO,
    ACCEPT,
    ERROR
};

class ParsingTable {
public:
    static std::map<int, std::pair<std::string, std::vector<std::string>>> getReductions(const std::string &path);

    static std::map<std::pair<std::string, int>, std::pair<ActionType, int>> getTable(const std::string &path);

private:
    static ActionType getActionType(const std::string &actionType);
};


#endif //OURLANG_PARSINGTABLE_H
