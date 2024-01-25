//
// Created by Camille De vuyst on 25/01/2024.
//

#include "prodRules.h"

prodRules::prodRules(const string &from, const string &to) : from(from), to(to) {}

prodRules::~prodRules() {

}
prodRules& prodRules::operator=(const prodRules& other) {
    if (this != &other) {
        from = other.from;
        to = other.to;
    }
    return *this;
}
