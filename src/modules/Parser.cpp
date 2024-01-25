#include "Parser.h"
#include <iostream>
#include <list>

#include "../datatypes/ParsingTable.h"

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

        switch (action.second.first) {
            case ActionType::SHIFT:
                // TODO look if tokens are used correctly
                // Push token from remaining output to parsing stack
                parsingStack.emplace(action.second.second);
                remainingTokens.pop_front();
                break;
//
            case ActionType::REDUCE:
                // Get production from parsing table
                rule = reductions.find(action.second.second)->second;

                // Reduce and push on stack
                parsingStack.emplace(*std::move(reduce(rule, parsingStack)));

                // Push goto to parsing stack
                // TODO check if slicing doens't occur
                parsingStack.emplace(table.find(std::make_pair(rule.first, stackTop))->second.second);

                break;
            case ActionType::ACCEPT:
                return program;
//                return std::get<Program>parsingStack.top();
            default:
                // Throw error
                throw std::runtime_error("Error: Parsing error");
        }
    }
    throw std::runtime_error("Error: Parsing error");
    return {{}};
}

std::unique_ptr<Statement>
Parser::reduce(const std::pair<std::string, std::vector<std::string>> &rule, std::stack<StackElement> &parsingStack) {
    // Pop from AST stack as many elements as the two time the size of the right hand side of the production
    std::vector<StackElement> poppedElements;
    for (int i = 0; i < rule.second.size() * 2; i++) {
        auto top = parsingStack.top();
        if (std::holds_alternative<Token>(top)) {
            poppedElements.emplace_back(std::get<Token>(top));
        }
        parsingStack.pop();
    }

    if (rule.first == "PROGRAM") {
        auto program = std::make_unique<Program>(Program({}));
        for (auto &element: poppedElements) {
            if (std::holds_alternative<Statement>(element)) {
                auto statement = std::get<Statement>(element);
                program->push_back(statement);
            } else {
                throw std::runtime_error("Error: Parsing error: element in stack is not a statement");
            }
        }
        return program;
//    } else if (rule.first == "BINARY_EXPRESSION") {


//        auto expression = std::make_unique<BinaryExpression>(BinaryExpression(std::get<Statement>(poppedElements.front()), ));
//        return expression;
//    } else if (rule.first == "Factor") {
//        return Statement(NodeType::Factor);
//    } else if (rule.first == "IfLoop") {
//        return Statement(NodeType::IfLoop);
//    } else if (rule.first == "ElseIfLoop") {
//        return Statement(NodeType::ElseIfLoop);
//    } else if (rule.first == "ElseLoop") {
//        return Statement(NodeType::ElseLoop);
//    } else if (rule.first == "WhileLoop") {
//        return Statement(NodeType::WhileLoop);
//    } else if (rule.first == "ForLoop") {
//        return Statement(NodeType::ForLoop);
//    } else if (rule.first == "Print") {
//        return Statement(NodeType::Print);
//    } else if (rule.first == "Input") {
//        return Statement(NodeType::Input);
//    } else if (rule.first == "Function") {
//        return Statement(NodeType::Function);
//    } else if (rule.first == "FunctionCall") {
//        return Statement(NodeType::FunctionCall);
//    } else if (rule.first == "Identifier") {
//        return Statement(NodeType::Identifier);
//    } else if (rule.first == "Integer") {
//        return Statement(NodeType::Integer);
//    } else if (rule.first == "Float") {
//        return Statement(NodeType::Float);
//    } else if (rule.first == "String") {
//        return Statement(NodeType::String);
//    } else if (rule.first == "Operator") {
//        return Statement(NodeType::Operator);
//    } else if (rule.first == "Comparison") {
//        return Statement(NodeType::Comparison);
//    } else if (rule.first == "FunctionName") {
//        return Statement(NodeType::FunctionName);
//    } else if (rule.first == "FunctionParameters") {
//        return Statement(NodeType::FunctionParameters);
//    } else if (rule.first == "Function){
//        return Statement(NodeType::Function);
    } else {
        throw std::runtime_error("Error: Parsing error");
    }
}
