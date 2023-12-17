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
    auto function = getFunction(name);

    // Execute the function with evaluated parameters
    return std::visit([&parameters](auto&& arg) -> Value {
        using T = std::decay_t<decltype(arg)>;

        // Original types
        if constexpr (std::is_same_v<T, float (*)(float)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<float>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for float function");
            }
            // Convert numeric types directly
            return arg(std::get<float>(parameters[0]));
        } else if constexpr (std::is_same_v<T, int (*)(int)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<int>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for int function");
            }
            // Convert numeric types directly
            return arg(std::get<int>(parameters[0]));
        } else if constexpr (std::is_same_v<T, bool (*)(bool)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<bool>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for bool function");
            }
            // Convert boolean to "true" or "false"
            return arg(std::get<bool>(parameters[0]));
        } else if constexpr (std::is_same_v<T, std::string (*)(std::string)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<std::string>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for string function");
            }
            // For string, return as is
            return arg(std::get<std::string>(parameters[0]));
        }

        // Additional types
        else if constexpr (std::is_same_v<T, int (*)(float)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<float>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for int function");
            }
            // Convert numeric types directly
            return arg(std::get<float>(parameters[0]));
        } else if constexpr (std::is_same_v<T, float (*)(int)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<int>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for float function");
            }
            // Convert numeric types directly
            return arg(std::get<int>(parameters[0]));
        } else if constexpr (std::is_same_v<T, bool (*)(int)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<int>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for bool function");
            }
            // Convert numeric types directly
            return arg(std::get<int>(parameters[0]));
        } else if constexpr (std::is_same_v<T, int (*)(bool)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<bool>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for int function");
            }
            // Convert numeric types directly
            return arg(std::get<bool>(parameters[0]));
        } else if constexpr (std::is_same_v<T, bool (*)(float)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<float>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for bool function");
            }
            // Convert numeric types directly
            return arg(std::get<float>(parameters[0]));
        } else if constexpr (std::is_same_v<T, float (*)(bool)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<bool>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for float function");
            }
            // Convert numeric types directly
            return arg(std::get<bool>(parameters[0]));
        } else if constexpr (std::is_same_v<T, std::string (*)(int)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<int>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for string function");
            }
            // Convert numeric types directly
            return arg(std::get<int>(parameters[0]));
        } else if constexpr (std::is_same_v<T, std::string (*)(float)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<float>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for string function");
            }
            // Convert numeric types directly
            return arg(std::get<float>(parameters[0]));
        } else if constexpr (std::is_same_v<T, std::string (*)(bool)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<bool>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for string function");
            }
            // Convert numeric types directly
            return arg(std::get<bool>(parameters[0]));
        } else if constexpr (std::is_same_v<T, int (*)(const std::string&)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<std::string>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for int function");
            }
            // Convert numeric types directly
            return arg(std::get<std::string>(parameters[0]));
        } else if constexpr (std::is_same_v<T, float (*)(const std::string&)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<std::string>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for float function");
            }
            // Convert numeric types directly
            return arg(std::get<std::string>(parameters[0]));
        } else if constexpr (std::is_same_v<T, bool (*)(const std::string&)>) {
            // Ensure correct parameter count and types
            if (parameters.size() != 1 || !std::holds_alternative<std::string>(parameters[0])) {
                throw std::runtime_error("Invalid arguments for bool function");
            }
            // Convert numeric types directly
            return arg(std::get<std::string>(parameters[0]));
        }
        // ... add more as needed

        throw std::runtime_error("Function type not supported");
    }, function);
}