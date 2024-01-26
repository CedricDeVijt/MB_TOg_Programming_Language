#include "ParsingTable.h"
#include <fstream>

#include "../datatypes/json.hpp"

using json = nlohmann::json;

ParsingTable::ParsingTable(const std::string &path) {
    // check if path is a json file
    if (path.substr(path.find_last_of('.') + 1) != "json") {
        throw std::invalid_argument("ParsingTable: path is not a json file");
    }

    // Open json file
    // Load parsing table from json file
    std::ifstream tableFile(path);
    if (!tableFile.is_open()) {
        // Handle file not found or other errors
        throw std::runtime_error("Error: Unable to open parsing table file.");
    }
    json tableJson;
    tableFile >> tableJson;

    // Reduction rules
    for (const auto &rule: tableJson["Reductions"]) {
        auto nr = rule["nr"].get<int>();
        auto left = rule["left"].get<std::string>();
        auto right = rule["right"].get<std::vector<std::string>>();

        reductions[nr] = std::make_pair(left, right);
    }

    for (const auto &entry: tableJson["Table"]) {
        auto col = entry["col"].get<std::string>();
        auto row = entry["row"].get<int>();
        auto type = entry["type"].get<std::string>();
        auto value = entry["value"].get<int>();

        table[std::make_pair(col, row)] = std::make_pair(getActionType(type), value);
    }
}

ActionType ParsingTable::getActionType(const std::string &actionType) {
    if (actionType == "SHIFT") {
        return ActionType::SHIFT;
    } else if (actionType == "REDUCE") {
        return ActionType::REDUCE;
    } else if (actionType == "GOTO") {
        return ActionType::GOTO;
    } else if (actionType == "ACCEPT") {
        return ActionType::ACCEPT;
    } else if (actionType == "ERROR") {
        return ActionType::ERROR;
    } else {
        throw std::runtime_error("Error: Invalid action type.");
    }
}

const std::map<int, std::pair<std::string, std::vector<std::string>>> &ParsingTable::getReductions() const {
    return reductions;
}

const std::map<std::pair<std::string, int>, std::pair<ActionType, int>> &ParsingTable::getTable() const {
    return table;
}