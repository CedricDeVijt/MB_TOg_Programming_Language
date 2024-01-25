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
    parsingStack.emplace(0); // initial state

    // Initialize Remaining Tokens
    Tokens remainingTokens = tokens;

    // Parser loop
    while (!parsingStack.empty()) {
        // Get top of parsing stack
        int stackTop =  getStackTop(parsingStack);

        // Get token from remaining output
        std::string token = getNextToken(remainingTokens);

        // Get action from parsing table
        auto action = *table.find(std::make_pair(token, stackTop));

        // Reduction rule if needed
        std::pair<std::string, std::vector<std::string>> rule;

        // Invoke action
        switch (action.second.first) {
            case ActionType::SHIFT:
                // TODO look if tokens are used correctly
                // Push token from remaining output to parsing stack
                parsingStack.emplace(action.second.second);
                remainingTokens.pop_front();
                break;

            case ActionType::REDUCE:
                // Get production from parsing table
                rule = reductions.find(action.second.second)->second;

                // Reduce and push on stack
                parsingStack.emplace(std::move(reduce(rule, parsingStack)));

                // Push goto to parsing stack
                // TODO check if slicing doesn't occur
                parsingStack.emplace(table.find(std::make_pair(rule.first, stackTop))->second.second);

                break;
            case ActionType::ACCEPT:
                if (std::holds_alternative<std::unique_ptr<Program>>(parsingStack.top())) {
                    auto result = *std::move(std::get<std::unique_ptr<Program>>(parsingStack.top()));
                    return result;
                } else {
                    throw std::runtime_error("Error: Parsing error: top of stack does not contain a statement");
                }
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
        if (std::holds_alternative<Token>(parsingStack.top()) or std::holds_alternative<std::unique_ptr<Statement>>(parsingStack.top())) {
            poppedElements.emplace_back(std::get<Token>(parsingStack.top()));

            parsingStack.pop();
        }

        if (rule.first == "PROGRAM") {
            auto program = std::make_unique<Program>(Program({}));
            for (auto &element: poppedElements) {
                if (std::holds_alternative<std::unique_ptr<Statement>>(element)) {
                    auto statement = *std::move(std::get<std::unique_ptr<Statement>>(element));
                    program->push_back(statement);
                } else {
                    throw std::runtime_error("Error: Parsing error: element in stack is not a statement");
                }
            }
            return program;

        } else if (rule.first == "BINARY_EXPRESSION") {
            auto left = *std::move(std::get<std::unique_ptr<Statement>>(poppedElements[0]));
            auto right = *std::move(std::get<std::unique_ptr<Statement>>(poppedElements[2]));
            auto op = std::get<Token>(poppedElements[1]).getValue();
            auto expression = std::make_unique<BinaryExpression>(BinaryExpression(left, right, op));
            return expression;

//    } else if (rule.first == "BODY") {
//    } else if (rule.first == "EXPRESSION") {
            // TODO what to do with an expression?
//        if (poppedElements.size() == 1){
//            return std::make_unique<Expression>(std::get<Statement>(poppedElements[0]));
//        } else {
//            throw std::runtime_error("Error: Parsing error");
//        }
//    } else if (rule.first == "EXPRESSION_LOOP") {
//    } else if (rule.first == "FUNCTION_CALL") {
        } else if (rule.first == "FUNCTION_DECLARATION") {
            auto name = std::get<Token>(poppedElements[0]).getValue();
            auto id = std::get<Token>(poppedElements[1]).getValue(); // TODO check if correct
            auto id_loop = *std::move(std::get<std::unique_ptr<Statement>>(poppedElements[3])); // TODO moet list van statements zijn
            auto body = *std::move(std::get<std::unique_ptr<Statement>>(poppedElements[5])); // TODO body moet list van statements zijn
            auto functionDeclaration = std::make_unique<FunctionDeclaration>(FunctionDeclaration(name, {}, {body}));
            return functionDeclaration;


//    } else if (rule.first == "ID_LOOP") {
//    } else if (rule.first == "IF_STATEMENT") {
        } else if (rule.first == "OP") {
            return std::make_unique<Identifier>(Identifier(rule.second[0]));

//    } else if (rule.first == "PROGRAM") {
//    } else if (rule.first == "RET_STATEMENT") {
        } else if (rule.first == "STATEMENT") {


//    } else if (rule.first == "STATEMENTS") {
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
        return "EOF";
    } else {
        TokenType tok = remainingTokens.front().getTokenType();
        return Token::tokenTypeToString(tok);
    }
}
