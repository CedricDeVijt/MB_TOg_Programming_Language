#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../datatypes/AST.h"

class Executor
{
public:
    static void execute(const AST &ast);
};

#endif