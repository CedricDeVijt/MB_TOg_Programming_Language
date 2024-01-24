#include "Parser.h"
#include <iostream>
#include "../datatypes/ParsingTable.h"

using StackElement = std::variant<TypeVariant, int>;

Program Parser::parse(const Tokens &tokens, const std::string &parserTablePath) {
    Program program({});

    // Load parsing table
    auto parsingTable = ParsingTable(parserTablePath);
    const auto &reductions = parsingTable.getReductions();
    const auto &table = parsingTable.getTable();

    // Initialize parsing stack
    std::stack<StackElement> parsingStack;
    parsingStack.emplace(0); // initial state

    // Initialize Remaining Tokens
    Tokens remainingTokens = tokens;

    // Parser loop
    while (!parsingStack.empty()) {
        // Get top of parsing stack
//        int stackTop = std::stoi(get<std::string>(parsingStack.top()));
        TypeVariant TokenType = remainingTokens.front().getTokenType();

        // Get action from parsing table
//        auto action = *table.find(std::make_pair(TokenType, stackTop));

//
//        switch (action.second.first) {
//            case ActionType::SHIFT:
//                // Push token from remaining output to parsing stack
//                parsingStack.emplace(remainingTokens.front());
//                remainingTokens.pop_front();
//
//                // Push state from parsing table to parsing stack
//                parsingStack.emplace(action.second.second);
//
//                break;
//            case ActionType::REDUCE:
//                // Get production from parsing table
//                // Pop from AST stack as many elements as the size of the right hand side of the production
//                // Push a new AST node to AST stack with the left hand side of the production as the label and the popped elements as the children
//                // Get state from parsing stack
//                // Get goto from parsing table
//                // Push goto to parsing stack
//                break;
//            case ActionType::GOTO:
//                // Push goto to parsing stack
//                break;
//            case ActionType::ACCEPT:
//                return program;
//            case ActionType::ERROR:
//                // Throw error
//                throw std::runtime_error("Error: Parsing error");
//        }
    }


    return program;
}