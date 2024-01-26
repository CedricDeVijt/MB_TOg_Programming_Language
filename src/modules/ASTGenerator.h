#ifndef OURLANG_ASTGENERATOR_H
#define OURLANG_ASTGENERATOR_H

#include "../datatypes/AST.h"
#include "LRParser.h"

class StackElement {
public:
    StackElement() = default;
    virtual ~StackElement() = default;
};

class Body: public StackElement {
public:
    Body() = default;
    std::list<std::unique_ptr<Statement>> body;
};

class AST: public StackElement {
public:
    AST() = default;
    std::unique_ptr<Statement> statement;
};

class ASTGenerator: public LRParser {
private:
    std::stack<std::shared_ptr<StackElement>> astStack;
    Tokens tokens;
    std::stack<Token> tokenStack;

public:
    explicit ASTGenerator(ParsingTable parsingTable);

public:
    Program generate(const Tokens &tokens_);

public:
    void shift() override;
    void reduce() override;

public:
    void setTokens(const Tokens &tokens_);
};


#endif //OURLANG_ASTGENERATOR_H
