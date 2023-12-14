//============================================================================
// Name        : Environment.h
// Author      : Siebe Mees
// Version     : 2.0
// Copyright   : Machines and Computability - BA2 Informatica - Siebe Mees - University of Antwerp
// Description : Environment is a C++ class for managing hierarchical settings and I/O streams.
//============================================================================

#ifndef MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H
#define MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H

#include <iostream>
#include <map>
#include <string>

class Env {
private:
    std::istream* stdin;
    std::ostream* stdout;
    std::ostream* stderr;
    Env* parent;
    std::map<std::string, std::string> items; // TODO: value of map should be a variant type (see AST.h) instead of a string

public:
    Env(Env* parent = nullptr, std::istream* in = nullptr, std::ostream* out = nullptr, std::ostream* err = nullptr);

    std::string get(const std::string& name);
    void set(const std::string& name, const std::string& value);
    bool contains(const std::string& name) const;
    std::string toString() const;
};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H
