//
// Created by Siebe Mees on 03/12/2023.
//

#ifndef MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H
#define MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H

#include <map>
#include <string>
#include <memory>
#include <variant>

// Define a variant type for different variable types
using VariableValue = std::variant<int, float, std::string, bool>;

class Environment : public std::enable_shared_from_this<Environment> {
private:
    std::map<std::string, VariableValue> items;
    std::shared_ptr<Environment> parentScope;
public:
    Environment(std::shared_ptr<Environment> parent = nullptr);

    void setVariable(const std::string& name, const VariableValue& value);
    VariableValue getVariable(const std::string& name) const;
    std::shared_ptr<Environment> createChildScope();
};


#endif //MB_TOG_PROGRAMMING_LANGUAGE_ENVIRONMENT_H
