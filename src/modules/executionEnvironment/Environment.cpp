//============================================================================
// Name        : Environment.h
// Author      : Siebe Mees
// Version     : 2.0
// Copyright   : Machines and Computability - BA2 Informatica - Siebe Mees - University of Antwerp
// Description : Environment is a C++ class for managing hierarchical settings and I/O streams.
//============================================================================

#include "Environment.h"
#include <cassert>
#include <sstream>

Env::Env(Env* parent, std::istream* in, std::ostream* out, std::ostream* err)
        : parent(parent), stdin(in), stdout(out), stderr(err) {
    if (parent != nullptr) {
        assert(stdin == nullptr && stdout == nullptr && stderr == nullptr);
        stdin = parent->stdin;
        stdout = parent->stdout;
        stderr = parent->stderr;
    }
}

Value Env::get(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) {
        return it->second;
    } else if (parent != nullptr) {
        return parent->get(name);
    }
    throw std::runtime_error("Variable not found: " + name);
}

Function Env::getFunction(const std::string& name) {
    auto it = functions.find(name);
    if (it != functions.end()) {
        return it->second;
    } else if (parent != nullptr) {
        return parent->getFunction(name);
    }
    throw std::runtime_error("Function not found: " + name);
}

void Env::set(const std::string& name, const Value& value) {
    items[name] = value;
}

void Env::setFunction(const std::string& name, const Function& function) {
    functions[name] = function;
}

bool Env::contains(const std::string& name) const {
    return items.find(name) != items.end();
}

bool Env::containsFunction(const std::string& name) const {
    return functions.find(name) != functions.end();
}

// Helper function to convert a Value (variant) to a string
std::string variantValueToString(const Value& value) {
    return std::visit([](auto&& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        std::ostringstream stream;

        if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>) {
            // Convert numeric types directly
            stream << arg;
        } else if constexpr (std::is_same_v<T, bool>) {
            // Convert boolean to "true" or "false"
            stream << (arg ? "true" : "false");
        } else if constexpr (std::is_same_v<T, std::string>) {
            // For string, return as is
            stream << arg;
        }

        return stream.str();
    }, value);
}

std::string Env::toString() const {
    std::string ret;
    for (const auto& item : items) {
        ret += item.first + "=" + variantValueToString(item.second) + "\n";
    }
    ret += ".\n" + (parent ? parent->toString() : "nullptr");
    return ret;
}

Value Env::executeFunction(const std::string &name, const std::vector<Value> &parameters) {
    // Retrieve the function from the environment
    auto functionIter = functions.find(name);
    if (functionIter == functions.end()) {
        throw std::runtime_error("Function " + name + " not found");
    }

    // Assuming the function is stored as std::function<Value(const std::vector<Value>&)>
    Function& function = functionIter->second;

    // Execute the function with evaluated parameters
    return function(parameters);
}
