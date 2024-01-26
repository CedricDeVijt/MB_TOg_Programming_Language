#include "ASTGenerator.h"
#include <utility>

ASTGenerator::ASTGenerator(ParsingTable parsingTable): LRParser(std::move(parsingTable)) {}

Program ASTGenerator::generate(const Tokens &tokens_) {
    setTokens(tokens_);
    if (parse()) {
        std::shared_ptr<AST> ast = std::static_pointer_cast<AST>(astStack.top());
        Program *p = dynamic_cast<Program*>(ast->statement.get());
        ast->statement.release();
        return std::move(*p);
    } else {
        return Program({});
    }
}

void ASTGenerator::shift() {
    LRParser::shift();
    tokenStack.push(tokens.front());
    tokens.pop_front();
}


void ASTGenerator::reduce() {
    auto action = *parsingTable.getTable().find(std::make_pair((input.empty() ? "$" : input.front()), intStack.top()));
    auto reduction = parsingTable.getReductions().find(action.second.second)->second;

    LRParser::reduce();

    if (reduction.first == "STATEMENTS") {
        if (reduction.second == std::vector<std::string>{"STATEMENTS", "STATEMENT"}) {
            std::shared_ptr<AST> ast = std::static_pointer_cast<AST>(astStack.top());
            astStack.pop();
            std::static_pointer_cast<Body>(astStack.top())->body.push_back(std::move(ast->statement));
        } else if (reduction.second.empty()) {
            astStack.push(std::make_unique<Body>());
        }
    } else if (reduction.first == "STATEMENT") {
        // do nothing because it is already a statement inherited
    } else if (reduction.first == "PROGRAM") {
        std::shared_ptr<Body> body = std::static_pointer_cast<Body>(astStack.top());
        astStack.pop();
        std::shared_ptr<AST> ast = std::make_shared<AST>();
        ast->statement = std::make_unique<Program>(std::move(body->body));
        astStack.push(ast);
        tokenStack.pop();
    } else if (reduction.first == "FACTOR") {
        if (reduction.second == std::vector<std::string>{"float"}) {
            std::shared_ptr<AST> ast = std::make_shared<AST>();
            ast->statement = std::make_unique<Float>(std::stof(tokenStack.top().getValue()));
            tokenStack.pop();
            astStack.push(ast);
        }
    } else if (reduction.first == "VAR_ASSIGN_STATEMENT") {
        std::shared_ptr<AST> ast = std::static_pointer_cast<AST>(astStack.top());
        astStack.pop();
        std::unique_ptr<Expression> exp;
        Expression *tmp = dynamic_cast<Expression*>(ast->statement.get());
        ast->statement.release();
        exp.reset(tmp);

        std::string id = tokenStack.top().getValue();
        tokenStack.pop();
        tokenStack.pop();

        std::shared_ptr<AST> newAst = std::make_shared<AST>();
        newAst->statement = std::make_unique<AssignmentStatement>(Identifier(id), std::move(exp));
        astStack.push(newAst);
    }
    else {
        std::string rest;
        for (const auto &s: reduction.second) {
            rest += s + " ";
        }
        throw std::runtime_error("AST CONSTRUCTION NOT YET IMPLEMENTED FOR REDUCUCTION: " + reduction.first + " -> " + rest);
    }
}

void ASTGenerator::setTokens(const Tokens &tokens_) {
    tokens = tokens_;
    input.clear();
    for (const auto &t: tokens) {
        input.push_back(Token::tokenTypeToString(t.getTokenType()));
    }
}