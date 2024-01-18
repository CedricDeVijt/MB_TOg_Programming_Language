#include "Parser.h"
#include <iostream>
#include <fstream>
#include "../utilities/ParserTableLoader.h"

Program Parser::parse(const Tokens &tokens, const std::string& parserTablePath) {
    Program program({});

    // get paring table from json file
    ParsingTable parsingTable = ParserTableLoader::getParserTable(parserTablePath);

//    // Initialize parsing stack
//    std::stack<StackElement> parsingStack;
//
//    // Push initial state to parsing stack
//    parsingStack.push(0);
//
//    // Token iterator
//    auto tokenIter = tokens.begin();
//
    // Parser loop

//    // While parsing stack is not empty
//    while (!parsingStack.empty()){
//        // Get top of parsing stack
//        auto stackTop = parsingStack.top();
//
//        // Get next token from input
//        auto token = *tokenIter;
//
//        // Get action from parsing table
//        auto action = parsingTable[std::make_pair(stackTop, token.getTokenType())];
//
//        switch (action) {
//            case SHIFT:
//                // Push token to AST stack
//                // Push state to parsing stack
//                break;
//            case REDUCE:
//                // Get production from parsing table
//                // Pop from AST stack as many elements as the size of the right hand side of the production
//                // Push a new AST node to AST stack with the left hand side of the production as the label and the popped elements as the children
//                // Get state from parsing stack
//                // Get goto from parsing table
//                // Push goto to parsing stack
//                break;
//            case GOTO:
//                // Push goto to parsing stack
//                break;
//            case ACCEPT:
//                // Break
//                break;
//            case ERROR:
//                // Throw error
//                break;
//        }
//    }


    return program;
}