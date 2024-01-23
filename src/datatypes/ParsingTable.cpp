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
        // split string into vector of strings with delimiter "->"


    }

    // Table
    for (const auto &entry: tableJson["Table"]) {
        auto col = entry["col"].get<std::string>();
        auto row = entry["row"].get<int>();
        auto type = entry["type"].get<std::string>();
        auto value = entry["value"].get<int>();

        table[std::make_pair(getNodeType(col), row)] = std::make_pair(getActionType(type), value);
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

NodeType ParsingTable::getNodeType(const std::string &nodeType) {
    if (nodeType == "Program") {
        return NodeType::Program;
    } else if (nodeType == "Float") {
        return NodeType::Float;
    } else if (nodeType == "String") {
        return NodeType::String;
    } else if (nodeType == "Bool") {
        return NodeType::Bool;
    } else if (nodeType == "Identifier") {
        return NodeType::Identifier;
    } else if (nodeType == "BinaryExpression") {
        return NodeType::BinaryExpression;
    } else if (nodeType == "FunctionCall") {
        return NodeType::FunctionCall;
    } else if (nodeType == "FunctionDeclaration") {
        return NodeType::FunctionDeclaration;
    } else if (nodeType == "IfStatement") {
        return NodeType::IfStatement;
    } else if (nodeType == "AssignmentStatement") {
        return NodeType::AssignmentStatement;
    } else if (nodeType == "WhileStatement") {
        return NodeType::WhileStatement;
    } else {
        throw std::runtime_error("Error: Invalid node type.");
    }
}


const std::map<TokenVariant, TokenVariants> &ParsingTable::getReductions() const {
    return reductions;
}

const std::map<std::pair<TokenVariant, int>, std::pair<ActionType, int>> &ParsingTable::getTable() const {
    return table;
}
