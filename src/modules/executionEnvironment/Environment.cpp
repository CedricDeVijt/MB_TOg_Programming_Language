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

Env::Env(std::shared_ptr<Env> parent, std::shared_ptr<std::istream> in, std::shared_ptr<std::ostream> out, std::shared_ptr<std::ostream> err)
    : parent(parent), stdin(in), stdout(out), stderr(err) {
    if (parent != nullptr) {
        assert(stdin == nullptr && stdout == nullptr && stderr == nullptr);
        stdin = parent->stdin;
        stdout = parent->stdout;
        stderr = parent->stderr;
    }

    // Add built-in functions
    setFunction("print", [this](const std::vector<Value>& args) { return this->print(args); });
    setFunction("input", [this](const std::vector<Value>&) { return this->input(); });
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

Value Env::print(const std::vector<Value>& args) {
    // Check if the output stream pointer is valid and the stream is in a good state
    if (!stdout || !stdout->good()) {
        throw std::runtime_error("Output stream not available or in a bad state.");
    }

    // Clear any error flags that might be set on the stream
    stdout->clear();

    for (const auto& arg : args) {
        *stdout << variantValueToString(arg);
        // Check if the stream is in a bad state after the write operation
        if (stdout->fail()) {
            throw std::runtime_error("Failed to write to output stream.");
        }
    }

    // Write a newline and check the stream state again
    *stdout << std::endl;
    if (stdout->fail()) {
        throw std::runtime_error("Failed to write newline to output stream.");
    }

    return {};
}

Value Env::input() {
    if (!stdin) {
        throw std::runtime_error("Input stream not available.");
    }

    std::string line;
    if (std::getline(*stdin, line)) {
        return line;  // Successfully read a line
    } else {
        // Handle input error
        throw std::runtime_error("Failed to read from input stream.");
    }
}