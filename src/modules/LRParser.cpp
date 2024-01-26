#include "LRParser.h"
#include <utility>

LRParser::LRParser(ParsingTable parsingTable): parsingTable(std::move(parsingTable)) {}

bool LRParser::parse() {
    auto reductions = parsingTable.getReductions();
    auto table = parsingTable.getTable();

    intStack = std::stack<int>();
    intStack.push(0);

    while (true) {
        auto it = table.find(std::make_pair((input.empty() ? "$" : input.front()), intStack.top()));
        if (it == table.end()) {
            return false;
        }
        switch (it->second.first) {
            case ActionType::SHIFT:
                shift(); break;
            case ActionType::REDUCE:
                reduce(); break;
            case ActionType::ACCEPT:
                return true;
            default:
                return false;
        }
    }
}

void LRParser::shift() {
    auto action = *parsingTable.getTable().find(std::make_pair((input.empty() ? "$" : input.front()), intStack.top()));
    input.pop_front();
    intStack.push(action.second.second);
}

void LRParser::reduce() {
    auto action = *parsingTable.getTable().find(std::make_pair((input.empty() ? "$" : input.front()), intStack.top()));
    auto reduction = parsingTable.getReductions().find(action.second.second)->second;

    for (int i = 0; i < reduction.second.size(); ++i) {
        intStack.pop();
    }
    intStack.push(parsingTable.getTable().find(std::make_pair(reduction.first, intStack.top()))->second.second);
}

void LRParser::setInput(const std::list<std::string> &input_) {
    input = input_;
}