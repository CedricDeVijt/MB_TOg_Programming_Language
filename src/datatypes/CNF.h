//
// Created by Camille De vuyst on 25/01/2024.
//

#ifndef MB_TOG_PROGRAMMING_LANGUAGE_CNF_H
#define MB_TOG_PROGRAMMING_LANGUAGE_CNF_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "json.hpp"
#include "prodRules.h"
#include <algorithm>
#include <sstream>


using namespace std;
using json = nlohmann::json;




class CNF {


public:

    json j;
    void print();
    CNF(const string& file);
    void toCNF();
    virtual ~CNF();
    void epsilonProduction();
    void unitProduction();
    void uselessSymbols();
    static bool compareRules(const prodRules& rule1, const prodRules& rule2);
    void replacingTerminals();
    void rewriteProducts();
    void replacebody(string& stringTobeConstructed,  string& replacement, int& i);
    void createNewsymbol( prodRules& p);
    void existSingleProductie(string& terminal, vector<prodRules> &prod);
    void createNewsymbolExtra(string& terminal, vector<prodRules> &rules2);
    bool isStringComposedOfVectorElements2( std::string str, const std::vector<std::string>& elements);
    void createNewVar(string& strtoBeconstructed, string& fromvar, vector<prodRules>& R3, map<string,int>& keep);
    bool isCorrectSize(string& tostring);

    bool isStringComposedOfVectorElements( string str, const vector<string>& elements);
    bool foundOne(const string& str, const std::vector<std::string>& elements);
    void toJson();


private:
    string StartState;
    vector<string> Variables;
    vector<string> Terminals;
    std::map<std::string, std::vector<std::string>> Rules;
    vector<prodRules> prodRegels;


};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_CNF_H
