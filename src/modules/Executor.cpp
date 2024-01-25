//
// Created by Siebe Mees on 11/12/2023.
//

#include "Executor.h"

Executor::Executor(Env& env) : env(env) {}

bool isNotZeroOrEmpty(const Value& val) {
    return std::visit([](auto&& arg) -> bool {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>) {
            return arg != 0; // For numerical types, check if not equal to 0
        } else if constexpr (std::is_same_v<T, std::string>) {
            return !arg.empty(); // For string, check if not empty
        } else if constexpr (std::is_same_v<T, bool>) {
            return arg; // For bool, true is "not empty", false is "empty"
        } else {
            return true; // You can decide how to treat other types
        }
    }, val);
}

Value Executor::execute(const Program& program) {
    for (const auto& statement : program.getBody()) {
        evalStatement(statement);
    }
    if (isNotZeroOrEmpty(returnValue)) {
        return returnValue;
    }
    return 0;
}

void Executor::evalStatement(const std::unique_ptr<Statement>& statement) {
    switch (statement->getKind()) {
        case NodeType::AssignmentStatement:
            evalAssignment(statement.get());
            break;
        case NodeType::FunctionDeclaration:
            evalFunctionDeclaration(statement.get());
            break;
        case NodeType::IfStatement:
            evalIfStatement(statement.get());
            break;
        case NodeType::WhileStatement:
            evalWhileStatement(statement.get());
            break;
        case NodeType::ReturnStatement:
            returnValue = evalReturnStatement(statement.get(), env);
            break;
        default:
            throw std::runtime_error("Invalid statement type");
    }
}

Value Executor::evalExpression(const Expression &expression, Env& env) {
    /* TODO: Implement this
     * switch (expression.getKind()) {
        case NodeType::BinaryExpression:
            return evalBinaryExpression();
        default:
            return expression.evaluate(env);
    }*/
    if (expression.getKind() == NodeType::Identifier) {
        auto identifier = expression.evaluate(env);
        return env.get(std::get<std::string>(identifier));
    }
    return expression.evaluate(env);
}

void Executor::evalAssignment(const Statement* statement) {
    auto assignmentStatement = dynamic_cast<const AssignmentStatement*>(statement);
    auto left = assignmentStatement->getVariable();
    auto right = assignmentStatement->getValue();
    auto result = evalExpression(*right, env);
    env.set(left.getSymbol(), result);
}

void Executor::evalFunctionDeclaration(const Statement *statement) {
    auto funcDecl = dynamic_cast<const FunctionDeclaration*>(statement);
    if (!funcDecl) {
        throw std::runtime_error("Invalid statement type for function declaration");
    }

    std::string functName = funcDecl->getName();
    const auto& parameters = funcDecl->getParameters();
    const auto& body = funcDecl->getBody();

    // Create a std::function wrapper around the generic function wrapper
    Function func = [&body, &parameters, this, &functName](const std::vector<Value>& args) -> Value {
        // Check if arguments count matches the parameters count
        if (args.size() != parameters.size()) {
            throw std::runtime_error("Invalid number of arguments passed to function " + functName);
        }

        // Create a new scope for function execution
        Env newEnv(env); // env is the current environment

        // Set up arguments in the new scope
        auto paramIter = parameters.begin();
        auto argIter = args.begin();
        for (; paramIter != parameters.end(); ++paramIter, ++argIter) {
            newEnv.set(paramIter->get()->getSymbol(), *argIter);
        }

        // Execute each statement in the function body
        Value returnValue;
        for (const auto& stmt : body) {
            if (stmt->getKind() == NodeType::ReturnStatement) {
                returnValue = evalReturnStatement(stmt.get(), newEnv);
                break;
            }
            evalStatement(stmt);
        }

        return returnValue;
    };


    env.setFunction(functName, func);
}

void Executor::evalBinaryExpression(const Statement* statement) {
    // TODO: Implement this, already done in AST.cpp but wan that code in this file
}

Value Executor::evalReturnStatement(const Statement* statement, Env& newEnv) {// Dynamic cast to ensure statement is a ReturnStatement
    auto returnStatement = dynamic_cast<const ReturnStatement*>(statement);
    if (!returnStatement) {
        throw std::runtime_error("Expected a ReturnStatement");
    }

    // Assuming ReturnStatement has a method to get its expression
    const Expression* returnExpression = returnStatement->getExpression();
    if (!returnExpression) {
        throw std::runtime_error("ReturnStatement has no expression");
    }

    // Evaluate the expression in the context of newEnv
    // Assuming evalExpression is a method that takes an Expression and an Env
    return evalExpression(*returnExpression, newEnv);
}

bool isTruthy(const Value& value) {
    return std::visit([](const auto& v) -> bool {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, bool>) {
            return v; // For bool, return its value
        } else if constexpr (std::is_same_v<T, int> || std::is_same_v<T, float>) {
            return v != 0; // For int and float, true if not zero
        } else if constexpr (std::is_same_v<T, std::string>) {
            return !v.empty(); // For std::string, true if not empty
        } else {
            return true; // Default case, can be adjusted as needed
        }
    }, value);
}

void Executor::evalIfStatement(const Statement* statement) {
    // Assuming 'statement' is an IfStatement, and it has methods to access its condition, thenBlock, and elseBlock
    const IfStatement *ifStatement = dynamic_cast<const IfStatement *>(statement);
    if (!ifStatement) {
        throw std::runtime_error("Invalid statement type for evalIfStatement");
    }

    // Evaluate the condition
    Value conditionValue = evalExpression(*ifStatement->getCondition(), env);

    // Check the condition's truthiness and execute the corresponding block
    if (isTruthy(conditionValue)) {
        for (const auto &stmt: ifStatement->getThenBody()) {
            evalStatement(stmt);
        }
    } else if (ifStatement->getElseBody()) {
        evalStatement(ifStatement->getElseBody());
    }
}

void Executor::evalWhileStatement(const Statement* statement) {
    // Assuming 'statement' is a WhileStatement, and it has methods to access its condition and body
    const WhileStatement *whileStatement = dynamic_cast<const WhileStatement *>(statement);
    if (!whileStatement) {
        throw std::runtime_error("Invalid statement type for evalWhileStatement");
    }

    // Evaluate the condition
    Value conditionValue = evalExpression(*whileStatement->getCondition(), env);

    // Check the condition's truthiness and execute the body
    while (isTruthy(conditionValue)) {
        for (const auto &stmt: whileStatement->getBody()) {
            evalStatement(stmt);
        }
        conditionValue = evalExpression(*whileStatement->getCondition(), env);
    }
}

/*void Executor::evalPrintStatement(const Statement* statement) {
    // Assuming 'statement' is a PrintStatement, and it has a method to access its expression
    const PrintStatement *printStatement = dynamic_cast<const PrintStatement *>(statement);
    if (!printStatement) {
        throw std::runtime_error("Invalid statement type for evalPrintStatement");
    }

    printStatement->execute(env);
}

void Executor::evalInputStatement(const Statement* statement) {
    // Assuming 'statement' is an InputStatement, and it has a method to access its expression
    const InputStatement *inputStatement = dynamic_cast<const InputStatement *>(statement);
    if (!inputStatement) {
        throw std::runtime_error("Invalid statement type for evalInputStatement");
    }

    inputStatement->execute(env);
}*/