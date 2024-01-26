#ifndef OURLANG_LRPARSER_H
#define OURLANG_LRPARSER_H

#include "../datatypes/ParsingTable.h"
#include <stack>

class LRParser {
protected:
    ParsingTable parsingTable;
    std::list<std::string> input;
    std::stack<int> intStack;

public:
    explicit LRParser(ParsingTable parsingTable);

public:
    [[nodiscard]] bool parse();
    virtual void shift();
    virtual void reduce();

public:
    void setInput(const std::list<std::string> &input_);

};


#endif //OURLANG_LRPARSER_H
