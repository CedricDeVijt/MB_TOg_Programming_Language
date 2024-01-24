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
    explicit ParsingTable(const std::string &path);

private:
    std::map<int, std::pair<std::string, std::vector<std::string>>> reductions;
    std::map<std::pair<std::string, int>, std::pair<ActionType, int>> table;

public:
    [[nodiscard]]  std::map<int, std::pair<std::string, std::vector<std::string>>> getReductions();

    [[nodiscard]]  std::map<std::pair<std::string, int>, std::pair<ActionType, int>> getTable();

private:
    static ActionType getActionType(const std::string &actionType);
};


#endif //OURLANG_PARSINGTABLE_H
