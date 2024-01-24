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
#include <variant>
#include <vector>
#include <functional>

// Define a variant type that can hold different types of values
using Value = std::variant<float, int, std::string, bool>; // Add other types as needed

// Define a variant type that can hold different types of functions
// TODO: Consider rather using std::variant or std::function, which is the most efficient way to do this
using Function = std::function<Value(const std::vector<Value>&)>;
/*using Function = std::variant<
        std::monostate, // Represents a "null" function
        // Original types
        float (*)(float),
        int (*)(int),
        std::string (*)(std::string),
        bool (*)(bool),

        // Additional types
        int (*)(float),
        float (*)(int),
        bool (*)(int),
        int (*)(bool),
        bool (*)(float),
        float (*)(bool),
        std::string (*)(int),
        std::string (*)(float),
        std::string (*)(bool),
        int (*)(const std::string&),
        float (*)(const std::string&),
        bool (*)(const std::string&)
        // ... add more as needed
>;*/

class Env {
private:
    std::shared_ptr<std::istream> stdin;
    std::shared_ptr<std::ostream> stdout;
    std::shared_ptr<std::ostream> stderr;
    std::shared_ptr<Env> parent;
    std::map<std::string, Value> items;
    std::map<std::string, Function> functions;

public:
    Env(std::shared_ptr<Env> parent = nullptr, std::shared_ptr<std::istream> in = nullptr, std::shared_ptr<std::ostream> out = nullptr, std::shared_ptr<std::ostream> err = nullptr);

    Value get(const std::string& name);
    Function getFunction(const std::string& name);
    void set(const std::string& name, const Value& value);
    void setFunction(const std::string& name, const Function& function);

    bool contains(const std::string& name) const;
    bool containsFunction(const std::string& name) const;
    std::string toString() const;

    Value executeFunction(const std::string& name, const std::vector<Value>& parameters);

    Value print(const std::vector<Value>& args);
    Value input();
};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H
