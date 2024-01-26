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
private:
    std::map<int, std::pair<std::string, std::vector<std::string>>> reductions;
    std::map<std::pair<std::string, int>, std::pair<ActionType, int>> table;

public:
    ParsingTable(const std::string &path);

public:
    [[nodiscard]] const std::map<int, std::pair<std::string, std::vector<std::string>>> &getReductions() const;
    [[nodiscard]] const std::map<std::pair<std::string, int>, std::pair<ActionType, int>> &getTable() const;

private:
    static ActionType getActionType(const std::string &actionType);
};


#endif //OURLANG_PARSINGTABLE_H
