#ifndef OURLANG_PARSINGTABLE_H
#define OURLANG_PARSINGTABLE_H

#include <string>
#include <map>

#include "../datatypes/Token.h"
#include "../datatypes/AST.h"

using TokenVariant = std::variant<TokenType, NodeType>;
using TokenVariants = std::vector<TokenVariant>;

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
    std::map<TokenVariant, TokenVariants> reductions;
    std::map<std::pair<TokenVariant, int>, std::pair<ActionType, int>> table;

public:
    [[nodiscard]] const std::map<TokenVariant, TokenVariants> &getReductions() const;

    [[nodiscard]] const std::map<std::pair<TokenVariant, int>, std::pair<ActionType, int>> &getTable() const;

private:
    static static ActionType getActionType(const std::string &actionType);
    static NodeType getNodeType(const std::string &nodeType);
};


#endif //OURLANG_PARSINGTABLE_H
