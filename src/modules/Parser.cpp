#include "Parser.h"
#include <iostream>
#include "../datatypes/ParsingTable.h"

using StackElement = std::variant<std::string, int>;

Program Parser::parse(const Tokens &tokens, const std::string &parserTablePath) {
    Program program({});

    // Load parsing table
    auto parsingTable = ParsingTable(parserTablePath);
    auto reductions = parsingTable.getReductions();
    auto table = parsingTable.getTable();

    // Initialize parsing stack
    std::stack<StackElement> parsingStack;
    parsingStack.emplace(0); // initial state

    // Initialize Remaining Tokens
    Tokens remainingTokens = tokens;

    // Parser loop
    while (!parsingStack.empty()) {
        // Get top of parsing stack
        int stackTop;
        if (std::holds_alternative<int>(parsingStack.top())) {
            // Retrieve the value as an int
            stackTop = std::get<int>(parsingStack.top());
            // Now you can use the 'stackTop' variable
        } else {
            // Handle the case where the variant holds a std::string
            // You might want to add appropriate error handling or conversion logic here
            std::cerr << "Error: Top of parsing stack is not an int." << std::endl;
        }

        // Get token from remaining output
        std::string token;
        if (remainingTokens.empty()) {
            token = "EOF";
        } else {
            TokenType tok = remainingTokens.front().getTokenType();
            token = Token::tokenTypeToString(tok);
        }

        // Get action from parsing table
        auto action = *table.find(std::make_pair(token, stackTop));

        std::pair<std::string, std::vector<std::string>> rule;
        std::vector<std::string> poppedElements;
        std::pair<ActionType, int> gotoAction;


        switch (action.second.first) {
            case ActionType::SHIFT:
                // Push token from remaining output to parsing stack
                parsingStack.emplace(action.second.second);
                remainingTokens.pop_front();
                break;

            case ActionType::REDUCE:
                // Get production from parsing table
                rule = reductions.find(action.second.second)->second;
                // Pop from AST stack as many elements as the size of the right hand side of the production
                for (int i = 0; i < rule.second.size() * 2; i++) {
                    auto top = parsingStack.top();
                    if (std::holds_alternative<std::string>(parsingStack.top())) {
                        poppedElements.push_back(std::get<std::string>(parsingStack.top()));
                    }
                    parsingStack.pop();
                }

                // Push non-terminal from production to parsing stack
                parsingStack.emplace(rule.first);

                // Get goto from parsing table
                gotoAction = table.find(std::make_pair(rule.first, stackTop))->second;
                // Push goto to parsing stack
                parsingStack.emplace(gotoAction.second);

                // Add rule to AST
                // TODO: Add rule to AST

                break;
            case ActionType::ACCEPT:
                return program;
            default:
                // Throw error
                throw std::runtime_error("Error: Parsing error");
        }
    }
    throw std::runtime_error("Error: Parsing error");
}
