//
// Created by Siebe Mees on 03/12/2023.
//

#include "Environment.h"

void Environment::setVariable(const std::string& name, const VariableValue& value) {
    variables[name] = value;
}

VariableValue Environment::getVariable(const std::string& name) const {
    return variables.at(name);
}

