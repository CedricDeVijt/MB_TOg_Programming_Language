//
// Created by Camille De vuyst on 25/01/2024.
//

#include "CNF.h"

CNF::CNF(const string& file){
    ifstream input(file);
    json j;
    input >> j;
    string to;
    vector<string> vec;

    for (auto &charcter: j["Variables"]) {
        Variables.push_back(charcter.get<string>());
    }
    for (auto &terminals: j["Terminals"]) {
        Terminals.push_back(terminals.get<string>());
    }
    for (auto &state: j[ "Productions"]) {
        to.clear();
        std::string from = state["head"];

        for (auto &body : state["body"]) {
            if (!to.empty() && state["body"].size() > 1) {
                to += " "; // Voeg een spatie toe als to niet leeg is en er meer dan één variabele is
            }
            to += body.get<string>();
        }
        prodRules p(from, to);
        prodRegels.emplace_back(p);
    }

    StartState = j["Start"];


}

vector<string> epsilonVar;
vector<std::pair<string, string>> UnitPair;
vector<string> reachable;
vector<string>UsefulSymbols;
vector<string> generating;
vector<string> NewTer;
int countUnit = 0;
int countRemoved = 0;
int countRemovedTer= 0;
int countRemovedPRodrules = 0;
int countNewVar = 0;
int countNew = 0;



void CNF::toCNF(){


    /*
    int sizeOrg = prodRegels.size();
    cout << "Original CFG:" << endl;
    cout << "\n";
    print();
    cout<< "\n";
    cout << "-------------------------------------" << endl;
    cout<< "\n";
    */

    epsilonProduction();

    /*
    cout << " >> Eliminating epsilon productions" << endl;
    std::sort(epsilonVar.begin(), epsilonVar.end());
    cout << "    Nullables are {";
    for (size_t i = 0; i < epsilonVar.size(); ++i) {
        std::cout << epsilonVar[i];
        if (i < epsilonVar.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    cout << "    Created " <<  prodRegels.size() << " productions, original had " <<  sizeOrg  << endl;
    cout << "\n";
    print();
    cout<< "\n";
    int prdor = prodRegels.size();
    */


    unitProduction();

    /*
    cout << " >> Eliminating unit pairs" << endl;
    cout << "    Found " << countUnit << " unit productions" << endl;
    std::sort(UnitPair.begin(), UnitPair.end());
    cout << "    Unit pairs: {";
    for (size_t i = 0; i < UnitPair.size(); ++i) {
        std::cout << "(" << UnitPair[i].first << ", " << UnitPair[i].second << ")";
        if (i < UnitPair.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    cout << "    Created " << prodRegels.size()<<" new productions, original had " << prdor << endl;
    cout << "\n";
    print();
    cout<< "\n";
    */

    uselessSymbols();

    /*
    cout << " >> Eliminating useless symbols" << endl;
    for(auto &i: Terminals){
        generating.emplace_back(i);
    }
    std::sort(generating.begin(), generating.end());
    cout << "    Generating symbols: {";
    for (size_t i = 0; i < generating.size(); ++i) {
        std::cout << generating[i];
        if (i < generating.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;



    std::sort(reachable.begin(), reachable.end());
    cout << "    Reachable symbols: {" ;
    for (size_t i = 0; i < reachable.size(); ++i) {
        std::cout << reachable[i];
        if (i < reachable.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    std::sort(UsefulSymbols.begin(), UsefulSymbols.end());
    cout << "    Useful symbols: {";
    for (size_t i = 0; i < UsefulSymbols.size(); ++i) {
        std::cout << UsefulSymbols[i];
        if (i < UsefulSymbols.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    cout << "    Removed " << countRemoved << " variables, " << countRemovedTer <<" terminals and " <<  countRemovedPRodrules << " productions" << endl;
    cout << "\n";
    print();
    cout<< "\n";

    int countprodRules = prodRegels.size();

    */
    replacingTerminals();
    /*

    std::sort(NewTer.begin(), NewTer.end());
    cout << " >> Replacing terminals in bad bodies" << endl;
    cout << "    Added " << countNew << " new variables: {" ;
    for (size_t i = 0; i < NewTer.size(); ++i) {
        std::cout << NewTer[i];
        if (i < NewTer.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    cout << "    Created " <<  prodRegels.size() << " new productions, original had " << countprodRules<< endl;
    cout << "\n";
    print();
    cout<< "\n";
    */


    rewriteProducts();

    /*
    cout << " >> Broke " << countNewVar << " bodies, added " << countNewVar <<" new variables" << endl;
    cout << ">>> Result CFG:" << endl;
    cout << "\n";

    */

    print();



}



void CNF::epsilonProduction(){

    //vector<string> epsilonVar;
    vector<prodRules> copyprod = prodRegels;

    //STAP 1 => kijk naar body die epislon bevatten en voeg die head toe aan de vector
    for(auto& product: copyprod){
        prodRules p = product;
        for (auto it = copyprod.begin(); it != copyprod.end(); ) {
            prodRules p = *it;
            if (p.to.empty()) {
                epsilonVar.emplace_back(p.from);
                it = copyprod.erase(it);
            } else {
                ++it;
            }
        }
    }

    //STAP 2 => kijk opnieuw welke body volledig bestaat uit een epsilon var, die ook toevoegen aan vec;
    bool addedNewElement = true;
    while (addedNewElement) {
        addedNewElement = false;
        for (auto &product: copyprod) {
            prodRules p = product;
            for (auto &epsilon: epsilonVar) {
                if (isStringComposedOfVectorElements(p.to, epsilonVar)) {
                    if (std::find(epsilonVar.begin(), epsilonVar.end(), product.from) == epsilonVar.end()) {
                        epsilonVar.emplace_back(p.from);
                        addedNewElement = true;
                    }
                }
            }
        }
    }

    //STAP 3 ALGORITME UITVOEREN
    bool NewElement = true;
    while (NewElement) {
        NewElement = false;
        std::vector<prodRules> updatedCopyprod;

        for (const auto& product : copyprod) {
            prodRules p = product;

            for (const auto& epsilon : epsilonVar) {
                std::string substring = epsilon;

                if (p.to.size() != 1) {
                    std::string mainString = p.to;
                    size_t found = mainString.find(substring);

                    if (found != std::string::npos) {
                        mainString.erase(found, 2);

                        // Use a lambda to check if the rule already exists
                        auto ruleExists = [&](const prodRules& existingRule) {
                            return existingRule.from == p.from && existingRule.to == mainString;
                        };

                        // Check if the updated rule already exists in the vector
                        if (std::find_if(copyprod.begin(), copyprod.end(), ruleExists) == copyprod.end() &&
                            std::find_if(updatedCopyprod.begin(), updatedCopyprod.end(), ruleExists) == updatedCopyprod.end()) {
                            prodRules r(p.from, mainString);
                            updatedCopyprod.emplace_back(r);
                            NewElement = true;
                        }
                    }
                }
            }
        }

        // Concatenate the original rules with the new ones
        copyprod.insert(copyprod.end(), updatedCopyprod.begin(), updatedCopyprod.end());
    }

    prodRegels = copyprod;
}

void CNF::unitProduction() {

    //vector maken met alle mogelijke UNIT-PAIRS

    //STAP 1 => Basis Stap unit pairs
    for (auto &a: Variables) {
        UnitPair.emplace_back(std::make_pair(a, a));
    }

    for(auto& i:prodRegels){
        if(i.to.size() == 1){
            if (std::find(Variables.begin(), Variables.end(), i.to) != Variables.end()) {
                countUnit += 1;
            }
        }
    }

    // STAP 2 => INDUCTIE stap unit pairs
    bool New = true;
    while (New) {
        New = false;
        for (auto &u: prodRegels) {
            if (u.to.size() == 1) {
                if (std::find(Variables.begin(), Variables.end(), u.to) != Variables.end()) {
                    std::pair<std::string, std::string> newPair(u.from, u.to);
                    auto duplicateIt = std::find_if(UnitPair.begin(), UnitPair.end(),[&newPair](const std::pair<std::string, std::string>& existingPair) {
                        return existingPair == newPair;
                    });
                    if (duplicateIt == UnitPair.end()) {
                        UnitPair.push_back(newPair);
                    }
                }
            }
        }
        // nieuwe ProductieRegels toevoegen!
        for (auto &j: UnitPair) {
            for (auto p: prodRegels) {
                if (j.second == p.from) {
                    if (std::find_if(prodRegels.begin(), prodRegels.end(), [&](const prodRules &existingRule) {
                        return existingRule.from == j.first && existingRule.to == p.to;
                    }) == prodRegels.end()) {
                        prodRules pp(j.first, p.to);
                        prodRegels.emplace_back(pp);
                        New = true;
                    }
                }
            }
        }
    }

    //STAP 3 => verwijder de single variable regels!!
    for (auto it = prodRegels.begin(); it != prodRegels.end();) {
        prodRules p = *it;
        if (p.to.size() == 1 && std::find(Variables.begin(), Variables.end(), p.to) != Variables.end()) {
            it = prodRegels.erase(it);
        } else {
            ++it;
        }
    }

}

void CNF::uselessSymbols(){

    //Generalize; BASIS = { terminals }
    vector<string> basis ;
    vector<string> nonGeneraiting;
    basis = Terminals;

    bool newVar = true;
    while (newVar) {
        newVar = false;
        for (auto &p: prodRegels) {
            if (isStringComposedOfVectorElements(p.to, basis)) {
                if (std::find(basis.begin(), basis.end(), p.from) == basis.end()) {
                    basis.emplace_back(p.from);
                    newVar = true;
                }
            }
        }
    }
    //zoek alle variables die nit in basis zitten => die var met productieregels moet worden geëlimineerd
    for(auto& i:Variables){
        if (std::find(basis.begin(), basis.end(), i) ==  basis.end()){
            nonGeneraiting.emplace_back(i);
        }
        else{
            generating.emplace_back(i);
        }
    }
    for (auto it = prodRegels.begin(); it != prodRegels.end();) {
        prodRules p = *it;
        if(foundOne(p.from,nonGeneraiting) or foundOne(p.to, nonGeneraiting) ) {
            it = prodRegels.erase(it);
            countRemovedPRodrules += 1;
        } else {
            ++it;
        }
    }

    //REACHABLE; BASIS = { startSymbol }

    vector<string> nonReachable;
    reachable.emplace_back(StartState);

    bool newreach = true;
    while (newreach) {
        newreach = false;
        std::vector<std::string> toAdd;  // Temporary container
        for (auto itR = prodRegels.begin(); itR != prodRegels.end(); ++itR) {
            for (auto itI = reachable.begin(); itI != reachable.end(); ++itI) {
                if (itR->from == *itI) {
                    std::istringstream iss(itR->to);
                    std::string token;
                    while (iss >> token) {
                        if (std::find(reachable.begin(), reachable.end(), token) == reachable.end()) {
                            toAdd.push_back(token);
                            newreach = true;
                        }
                    }
                }
            }
        }
        std::sort(toAdd.begin(), toAdd.end());

        // Remove duplicates
        auto last = std::unique(toAdd.begin(), toAdd.end());
        toAdd.erase(last, toAdd.end());        // Add elements from the temporary container to the original container
        reachable.insert(reachable.end(), toAdd.begin(), toAdd.end());
    }

    //zoek alle symbolen die niet in reachable zitten => die var met productieregels moet worden geëlimineerd
    for(auto& i:Variables){
        if (std::find(reachable.begin(), reachable.end(), i) ==  reachable.end()){
            nonReachable.emplace_back(i);
        }

    }

    countRemoved = nonReachable.size();

    for (auto it = prodRegels.begin(); it != prodRegels.end();) {
        prodRules p = *it;
        if(foundOne(p.from,nonReachable) or foundOne(p.to, nonReachable) ) {
            it = prodRegels.erase(it);
            countRemovedPRodrules += 1;
        } else {
            ++it;
        }
    }

    //usefulSymbols bereken
    for(auto& g:basis){
        for(auto& r:reachable){
            if(g==r){
                UsefulSymbols.emplace_back(g);
            }
        }
    }
    vector<string> NewVariables;
    for(auto& v: Variables){
        for(auto& u: UsefulSymbols){
            if(v==u){
                NewVariables.emplace_back(v);
            }
        }

    }
    vector<string> NewTerminals;
    for(auto& v: Terminals){
        for(auto& u: UsefulSymbols){
            if(v==u){
                NewTerminals.emplace_back(v);
            }else{
            }
        }

    }
    countRemovedTer = Terminals.size() - NewTerminals.size();
    Variables = NewVariables;
    Terminals = NewTerminals;

}

void CNF::replacingTerminals() {

    vector<prodRules> Rules2;

    //STAP 1 de enkele Terminals tovoegen
    for(auto& p: prodRegels) {
        if (p.to.size() == 1 and isStringComposedOfVectorElements(p.to, Terminals)) {
            int count = std::count_if(prodRegels.begin(), prodRegels.end(),
                                      [&p](const prodRules &pr) { return pr.from == p.from; });
            if (count == 1) {
                Rules2.emplace_back(p);
            } else {
                createNewsymbol(p);
                Rules2.emplace_back(p);
            }
        }
    }
    for(auto& r: prodRegels){
        //stap 2 als de size >= 2 dan toevogen als helemaal varibalen, anders construct;
        if(r.to.size()>= 2){
            if(isStringComposedOfVectorElements(r.to, Variables)){
                Rules2.emplace_back(r);
            }else {
                bool newTer = true;
                while (newTer) {
                    newTer = false;
                    for (auto terminal: Terminals) {
                        for (int t = 0; t < r.to.size(); t++) {
                            char c = static_cast<char>(terminal[0]);
                            if (r.to[t] == c) {
                                existSingleProductie(terminal, Rules2);
                                for (auto &i: prodRegels) {
                                    if (i.to == terminal) {
                                        replacebody(r.to, i.from, t);
                                        t += i.from.size();
                                        if (isStringComposedOfVectorElements2(r.to, Variables)) {
                                            Rules2.emplace_back(r);
                                            newTer = false;
                                        } else {
                                            newTer = true;

                                        }
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    prodRegels = Rules2;
}

void CNF::rewriteProducts(){


    vector<prodRules> Rules3;
    map<string,int> keepUp;
    for(auto& v: Variables){
        keepUp[v]=1;
    }

    // STAP 1 voeg alle productie regels van een kleiner dan 3 toe aan de vector
    for (auto &p: prodRegels) {
        string to = p.to;
        to.erase(std::remove_if(to.begin(), to.end(),[](char c) { return std::isspace(c) || c == '_'; }),to.end());
        if (to.size() <= 2) {
            Rules3.emplace_back(p);
        }
    }

    // STAP 2 voor alle productie gelijk of groter dan 3 constructen naar 2 varibalen
    bool newVar = true;
    while (newVar) {
        newVar = false;
        for (auto &pr: prodRegels) {
            string prodTo = pr.to;
            prodTo.erase(std::remove_if(prodTo.begin(), prodTo.end(),[](char c) { return std::isspace(c) || c == '_'; }),prodTo.end());
            if (prodTo.size() >= 3) {
                createNewVar(pr.to, pr.from, Rules3, keepUp);
                if(isCorrectSize(pr.to)){
                    Rules3.emplace_back(pr);
                    newVar = false;

                }else{
                    newVar = true;
                }
            }
        }
    }



    prodRegels = Rules3;



}


void CNF::replacebody(string& stringTobeConstructed, string& replacement, int& i ){

    stringTobeConstructed.erase(i,1);
    stringTobeConstructed.insert(i,replacement);

}

void CNF::existSingleProductie(string& terminal, vector<prodRules> &rules2){
    auto it = std::find_if(prodRegels.begin(), prodRegels.end(),
                           [&terminal](const prodRules& pr) { return pr.to == terminal; });
    if (it == prodRegels.end()) {
        createNewsymbolExtra(terminal, rules2);

    }
}


void CNF::createNewsymbol(prodRules& p){

    string newString = "_" + p.to;
    prodRules productie(newString, p.to);
    prodRegels.emplace_back(productie);
    Variables.emplace_back(newString);

    for (auto it = prodRegels.begin(); it != prodRegels.end();) {
        prodRules itt = *it;
        if(itt.from == p.from and itt.to == p.to)  {
            it = prodRegels.erase(it);
        } else {
            ++it;
        }
    }

}

void CNF::createNewsymbolExtra(string& terminal, vector<prodRules> &rules2){
    string newString = "_" + terminal;
    prodRules productie(newString, terminal);
    countNew += 1;
    NewTer.emplace_back(newString);
    prodRegels.emplace_back(productie);
    rules2.emplace_back(productie);
    Variables.emplace_back(newString);

}


bool CNF::foundOne(const string& str, const std::vector<std::string>& elements){
    for (const std::string& element : elements) {
        if (str.find(element) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool CNF::isStringComposedOfVectorElements(std::string str, const std::vector<std::string>& elements) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    for (char ch : str) {
        std::string character(1, ch);
        if (std::find(elements.begin(), elements.end(), character) == elements.end()) {
            return false;
        }
    }
    return true;
}


bool CNF::isStringComposedOfVectorElements2(std::string str, const std::vector<std::string>& elements) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

    string resultString;
    for (std::size_t i = 0; i < str.size(); ++i) {
        char currentChar = str[i];
        if (currentChar == '_') {
            if (i + 1 < str.size()) {
                resultString = "_";
                resultString += str[i + 1];
                ++i;
            }
        } else {
            resultString = currentChar;
        }
        if (std::find(elements.begin(), elements.end(), resultString) == elements.end()) {
            return false;
        }
    }
    return true;
}

void CNF::createNewVar(string& strtoBeconstructed, string& fromvar, vector<prodRules>& R3, map<string,int>& keep){

    //cijfers aanpassen, door een map bij te houden en zo te tellen

    vector<string> varVec;  //vector voor de aparte variabelen
    string str = strtoBeconstructed; // copy van de de inputstring
    std::string variable; //tijdelijke variabelen
    std::istringstream iss(str);
    int cijfer = 0;
    string letter;
    string body;
    basic_string<char, char_traits<char>, allocator<char>> newfromvar;




    //body opdelen in aparte stukken en in string steken
    while (iss >> variable) {
        varVec.push_back(variable);
    }

    char mychar = fromvar[0];
    std::string resultString(1, mychar);

    for(auto& m: keep){
        if(m.first == resultString ){
            if(m.second == 1){
                cijfer = 2;
                m.second +=1;
            }
            else{
                cijfer = m.second + 1;
                m.second += 1;
            }

        }
    }

    body = varVec[1] + " " + varVec[2];
    string cijfer1 = to_string(cijfer);

    newfromvar = resultString + "_" + cijfer1;
    prodRules p(newfromvar, body);
    countNewVar += 1;
    R3.emplace_back(p);
    Variables.emplace_back(newfromvar);

    size_t found = strtoBeconstructed.find(body, 1);
    if (found != std::string::npos) {
        strtoBeconstructed.replace(found, body.length(), newfromvar);
    }

}

bool CNF::isCorrectSize(string& tostring){

    vector<string> vec;  //vector voor de aparte variabelen
    string str = tostring; // copy van de de inputstring
    std::string variable; //tijdelijke variabelen
    std::istringstream iss(str);

    while (iss >> variable) {
        vec.push_back(variable);
    }

    if(vec.size() == 2){
        return true;

    }else{
        return false;
    }


}




bool CNF::compareRules(const prodRules& rule1, const prodRules& rule2) {
    return rule1.from < rule2.from || (rule1.from == rule2.from && rule1.to < rule2.to);
}




void CNF::print() {
    std::sort(Variables.begin(), Variables.end());
    std::sort(Terminals.begin(), Terminals.end());


    cout << "V = {";
    for (auto i = 0; i < Variables.size(); i++) {
        cout << Variables[i];
        if (i < Variables.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}" << endl;

    cout << "T = {";
    for (auto j = 0; j < Terminals.size(); j++) {
        cout << Terminals[j];
        if (j < Terminals.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}" << endl;

    cout << "P = {" << endl;

    vector<prodRules> pr = prodRegels;

    for(auto& r:pr){
        r.to = "`" + r.to + "`";
    }


    std::sort(pr.begin(), pr.end(), compareRules);


    for (const auto& rule : pr) {
        prodRules p = rule;
        cout << "    " << p.from << " -> " << p.to  << endl;

    }
    cout << "}" << endl;

    cout << "S = " << StartState;
    cout <<"\n";


}
void CNF::toJson(){

    json j;

    for (const auto &variable : Variables) {
        j["Variables"] += variable;
    }

    for (const auto &terminal : Terminals) {
        j["Terminals"] += terminal;
    }


    j["Productions"] = json::array();
    for (const auto &transition : prodRegels) {
        const string &from_state = transition.from;
        const string &to_state = transition.to;
        json trans;
        trans["head"] = from_state;
        trans["body"] = to_state;
        j["transitions"].push_back(trans);

    }

    j["Start"] = StartState;


    std::ofstream file("output.json");
    file << std::setw(4) << j << std::endl;



}

CNF::~CNF() {

}


/*
int main() {
    CNF cfg("input-cnf1.json");
    cfg.toCNF();
    return 0;
}
 */