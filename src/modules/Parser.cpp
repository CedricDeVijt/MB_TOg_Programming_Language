#include "Parser.h"
#include <iostream>
#include <list>

#include "../datatypes/ParsingTable.h"

Program Parser::parse(const Tokens &tokens, const std::string &parserTablePath) {
    // Get reductions and parsing table
    auto reductions = ParsingTable::getReductions(parserTablePath);
    auto table = ParsingTable::getTable(parserTablePath);

    // Initialize parsing stack
    std::stack<StackElement> parsingStack;
    parsingStack.emplace(1); // initial state

    // Initialize Remaining Tokens
    Tokens remainingTokens = tokens;

    // Parser loop
    while (!parsingStack.empty()) {
        // Get top of parsing stack
        int stackTop = getStackTop(parsingStack);

        // Get token from remaining output
        std::string token = getNextToken(remainingTokens);

        // Get action from parsing table
        auto action = *table.find(std::make_pair(token, stackTop));

        // Reduction rule if needed
        std::pair<std::string, std::vector<std::string>> rule;

        // Invoke action
        switch (action.second.first) {
            case ActionType::SHIFT:
                // Push token from remaining output to parsing stack
                parsingStack.emplace(remainingTokens.front());
                remainingTokens.pop_front();
                // Push value from action to parsing stack
                parsingStack.emplace(action.second.second);
                break;

            case ActionType::REDUCE:
                // Get production from parsing table
                rule = reductions.find(action.second.second)->second;

                // Reduce stack and push new statement on stack
                reduceStack(rule, parsingStack);

                // Push goto to parsing stack
                parsingStack.emplace(table.find(std::make_pair(rule.first, stackTop))->second.second);
                break;

            case ActionType::ACCEPT:
                if (std::holds_alternative<std::unique_ptr<Program>>(parsingStack.top())) {
                    return std::move(*std::get<std::unique_ptr<Program>>(parsingStack.top()));
                } else {
                    throw std::runtime_error("Error: Parsing error: top of stack does not contain a program");
                }
            default:
                throw std::runtime_error("Error: Parsing error");
        }
    }
    throw std::runtime_error("Error: Parsing error");
}

void Parser::reduceStack(const std::pair<std::string, std::vector<std::string>> &rule,
                         std::stack<StackElement> &parsingStack) {
    // Pop from AST stack as many elements as the two time the size of the right hand side of the production
    std::vector<StackElement> poppedElements;
    for (int i = 0; i < rule.second.size() * 2; i++) {
        if (std::holds_alternative<Token>(parsingStack.top()) or
            std::holds_alternative<std::unique_ptr<Statement>>(parsingStack.top())) {
            poppedElements.emplace_back(std::get<Token>(parsingStack.top()));
            parsingStack.pop();
        }

        if (rule.first == "PROGRAM") {
            auto program = std::make_unique<Program>(Program({}));
            if (std::holds_alternative<std::list<std::unique_ptr<Statement>>>(poppedElements[0])) {
                parsingStack.emplace(std::move(std::get<std::list<std::unique_ptr<Statement>>>(poppedElements[0])));
            } else {
                throw std::runtime_error("Error: Parsing error: element in stack is not a statement");
            }

        } else if (rule.first == "EXPRESSION") {
            if (poppedElements.size() == 1) {
                if (std::holds_alternative<std::unique_ptr<Statement>>(poppedElements[0])) {
                    parsingStack.emplace(std::move(std::get<std::unique_ptr<Statement>>(poppedElements[0])));
                } else {
                    throw std::runtime_error("Error: Parsing error: element in stack is not a type of expression");
                }
            }

        } else if (rule.first == "FUNCTION_DECLARATION") {
            auto identifier = std::get<Token>(poppedElements[1]).getValue();
            auto IDLoop = std::move(std::get<std::list<std::unique_ptr<Identifier>>>(poppedElements[2]));
            auto body = std::move(std::get<std::list<std::unique_ptr<Statement>>>(poppedElements[4]));
            parsingStack.emplace(std::make_unique<FunctionDeclaration>(FunctionDeclaration(identifier, std::move(IDLoop), std::move(body))));

//    } else if (rule.first == "STATEMENT") {
        } else if (rule.first == "STATEMENTS") {
            std::list<std::unique_ptr<Statement>> statements;
            for (auto &element: poppedElements) {
                if (std::holds_alternative<std::unique_ptr<Statement>>(element)) {
                    statements.push_back(std::move(std::get<std::unique_ptr<Statement>>(element)));
                } else if (std::holds_alternative<std::list<std::unique_ptr<Statement>>>(element)) {
                    statements.splice(statements.end(),
                                      std::move(std::get<std::list<std::unique_ptr<Statement>>>(element)));
                } else {
                    throw std::runtime_error("Error: Parsing error: element in stack is not a statement");
                }
            }
//            return std::move(statements);
//    } else if (rule.first == "VAR_ASSIGN_STATEMENT") {
//    } else if (rule.first == "VAR_DECLARATION_STATEMENT") {
//    } else if (rule.first == "WHILE_STATEMENT") {
        } else {
            throw std::runtime_error("Error: Parsing error");
        }
    }
    throw std::runtime_error("Error: Parsing error");
}

int Parser::getStackTop(std::stack<StackElement> &parsingStack) {
    if (std::holds_alternative<int>(parsingStack.top())) {
        return std::get<int>(parsingStack.top());
    } else {
        throw std::runtime_error("Error: Parsing error: top of stack does not contain an int");
    }
}

std::string Parser::getNextToken(const Tokens &remainingTokens) {
    if (remainingTokens.empty()) {
        return "$";
    } else {
        TokenType tok = remainingTokens.front().getTokenType();
        return Token::tokenTypeToString(tok);
    }
}
