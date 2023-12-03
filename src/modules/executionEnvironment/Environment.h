//
// Created by Siebe Mees on 03/12/2023.
//

#ifndef MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H
#define MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H

#include <map>
#include <string>

#include <variant>

// Define a variant type for different variable types
using VariableValue = std::variant<int, double, std::string, bool>; // Add more types as needed

class Environment {
private:
    std::map<std::string, VariableValue> variables;
public:
    void setVariable(const std::string& name, const VariableValue& value);
    VariableValue getVariable(const std::string& name) const;
};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H
