#include <fstream>
#include "ParserTableLoader.h"
#include "../datatypes/json.hpp"

using json = nlohmann::json;

ParsingTable ParserTableLoader::getParserTable(const std::string&path) {
    ParsingTable parsingTable;

    // Load parsing table from json file
    std::ifstream tableFile(path);
    if (!tableFile.is_open()) {
        // Handle file not found or other errors
        throw std::runtime_error("Error: Unable to open parsing table file.");
    }

    json tableJson;
    tableFile >> tableJson;

    for (const auto&entry: tableJson.items()) {
        int state = std::stoi(entry.key()); // Convert the key to an integer

        for (const auto&tokenEntry: entry.value().items()) {
            TokenType tokenType = getTokenType(tokenEntry.key());
            std::pair<int, TokenType> key = {state, tokenType};

            TableEntry tableEntry{};
            // Populate ActionType and StackElement in tableEntry
            tableEntry.actionType = getActionType(tokenEntry.value()["actionType"].get<std::string>());

            try {
                tableEntry.state = std::stoi(tokenEntry.value()["state"].get<std::string>());
            }
            catch (const nlohmann::json::exception&e) {
            }

            // Add the entry to the ParsingTable
            parsingTable[{state, tokenType}] = tableEntry;
        }
    }
    return parsingTable;
}


TokenType ParserTableLoader::getTokenType(const std::string&token) {
    if (token == "IDENTIFIER") {
        return TokenType::IDENTIFIER;
    }
    else if (token == "VAR") {
        return TokenType::VAR;
    }
    else if (token == "IF") {
        return TokenType::IF;
    }
    else if (token == "ELSEIF") {
        return TokenType::ELSEIF;
    }
    else if (token == "ELSE") {
        return TokenType::ELSE;
    }
    else if (token == "WHILE") {
        return TokenType::WHILE;
    }
    else if (token == "FOR") {
        return TokenType::FOR;
    }
    else if (token == "OPENPAREN") {
        return TokenType::OPENPAREN;
    }
    else if (token == "CLOSEPAREN") {
        return TokenType::CLOSEPAREN;
    }
    else if (token == "EQUALS") {
        return TokenType::EQUALS;
    }
    else if (token == "COMMA") {
        return TokenType::COMMA;
    }
    else if (token == "PLUS") {
        return TokenType::PLUS;
    }
    else if (token == "MINUS") {
        return TokenType::MINUS;
    }
    else if (token == "DIVIDE") {
        return TokenType::DIVIDE;
    }
    else if (token == "TIMES") {
        return TokenType::TIMES;
    }
    else if (token == "EOFTOKEN") {
        return TokenType::EOFTOKEN;
    }
    else if (token == "INTEGER") {
        return TokenType::INTEGER;
    }
    else if (token == "STRING") {
        return TokenType::STRING;
    }
    else if (token == "GREATHERTHAN") {
        return TokenType::GREATHERTHAN;
    }
    else if (token == "LESSTHAN") {
        return TokenType::LESSTHAN;
    }
    else if (token == "BOOL") {
        return TokenType::BOOL;
    }
    else if (token == "FUNCTION") {
        return TokenType::FUNCTION;
    }
    else if (token == "FUNCTIONNAME") {
        return TokenType::FUNCTIONNAME;
    }
    else if (token == "PRINT") {
        return TokenType::PRINT;
    }
    else if (token == "USERINPUT") {
        return TokenType::USERINPUT;
    }
    else if (token == "INPUT") {
        return TokenType::INPUT;
    }
    else if (token == "COMMENT") {
        return TokenType::COMMENT;
    }
    else if (token == "FLOAT") {
        return TokenType::FLOAT;
    }
    else if (token == "LIMIT") {
        return TokenType::LIMIT;
    }
    else {
        throw std::runtime_error("Error: Unknown token type.");
    }
}

ActionType ParserTableLoader::getActionType(const std::string&actionType) {
    if (actionType == "SHIFT") {
        return ActionType::SHIFT;
    }
    else if (actionType == "REDUCE") {
        return ActionType::REDUCE;
    }
    else if (actionType == "GOTO") {
        return ActionType::GOTO;
    }
    else if (actionType == "ACCEPT") {
        return ActionType::ACCEPT;
    }
    else if (actionType == "ERROR") {
        return ActionType::ERROR;
    }
    else {
        throw std::runtime_error("Error: Unknown action type.");
    }
}
