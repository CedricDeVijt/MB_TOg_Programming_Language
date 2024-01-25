//
// Created by Camille De vuyst on 25/01/2024.
//

#ifndef MB_TOG_PROGRAMMING_LANGUAGE_PRODRULES_H
#define MB_TOG_PROGRAMMING_LANGUAGE_PRODRULES_H

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;


class prodRules {
public:

    prodRules& operator=(const prodRules& other);
    virtual ~prodRules();
    prodRules(const string &from, const string &to);

    string to;
    string from;

};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_PRODRULES_H
