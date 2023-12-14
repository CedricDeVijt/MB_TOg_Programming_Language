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
    return ""; // Or any other indication of "not found"
}

void Env::set(const std::string& name, const Value& value) {
    items[name] = value;
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