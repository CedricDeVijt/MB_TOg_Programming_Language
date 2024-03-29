//============================================================================
// Name        : CFG.h
// Author      : Siebe Mees
// Version     : 1.0
// Copyright   : Machines and Computability - BA2 Informatica - Siebe Mees - University of Antwerp
// Description : CFG is a C++ class for representing a context free grammar.
//============================================================================

#ifndef MB_TOG_PROGRAMMING_LANGUAGE_CFG_H
#define MB_TOG_PROGRAMMING_LANGUAGE_CFG_H

#include <string>
#include <vector>

class CFG {
private:
    std::vector<std::string> V; // Set of variables
    std::vector<std::string> T; // Set of terminals
    std::string S; // Start symbol
    std::vector<std::pair<std::string, std::vector<std::string>>> P; // Productions

public:
    CFG();

    CFG(const std::string &filename);
};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_CFG_H
