//
// Created by Siebe Mees on 03/12/2023.
//

#include "Environment.h"

Environment::Environment(std::shared_ptr<Environment> parent) : parentScope(parent) {}

void Environment::setVariable(const std::string& name, const VariableValue& value) {
    items[name] = value;
}

VariableValue Environment::getVariable(const std::string& name) const {
    auto it = items.find(name);
    if (it != items.end()) {
        return it->second;
    } else if (parentScope != nullptr) {
        return parentScope->getVariable(name);
    }
    throw std::runtime_error("Variable not found: " + name);
}

std::shared_ptr<Environment> Environment::createChildScope() {
    return std::make_shared<Environment>(shared_from_this());
}
