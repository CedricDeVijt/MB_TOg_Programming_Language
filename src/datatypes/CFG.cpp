//============================================================================
// Name        : CFG.cpp
// Author      : Siebe Mees
// Version     : 1.0
// Copyright   : Machines and Computability - BA2 Informatica - Siebe Mees - University of Antwerp
// Description : CFG is a C++ class for representing a context free grammar.
//============================================================================

#include "CFG.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

CFG::CFG() {}

CFG::CFG(const std::string &filename) {
    // inlezen uit file
    std::ifstream input(filename);

    json j;
    input >> j;

    // Access the elements of the "Start" array
    std::string start;
    for (const auto& startvar : j["Start"]) {
        start += startvar;
    }
    S = start;

    // Access the elements of the "Variables" array
    std::vector<std::string> variables;
    for (const auto& var : j["Variables"]) {
        variables.push_back(var);
    }
    sort(variables.begin(), variables.end());
    V = variables;

    // Access the elements of the "Terminals" array
    std::vector<std::string> terminals;
    for (const auto& terminal : j["Terminals"]) {
        terminals.push_back(terminal);
    }
    sort(terminals.begin(), terminals.end());
    T = terminals;

    // Access the elements of the "Productions" array
    std::vector<std::pair<std::string, std::vector<std::string>>> productions;
    for (const auto& rule : j["Productions"]) {
        std::string head = rule["head"];
        std::vector<std::string> body = rule["body"];
        productions.push_back(make_pair(head, body));
    }
    sort(productions.begin(), productions.end());
    P = productions;
}