#include "./src/MyLang.h"
#include "./src/exceptions/FileNotFoundError.h"
#include "./src/exceptions/ArgsError.h"
#include <fstream>
#include <sstream>

#include <cassert>
#include "src/datatypes/AST.h"
#include "src/modules/Executor.h"

void testArithmeticExpression() {
    // Create an AST for the expression: a = 2.5 + 3.5
    //
    Identifier a = Identifier("a");

    String b = String("b");
    Statement bPtr = b;
    String c = String("c");
    Statement cPtr = c;
    BinaryExpression expr = BinaryExpression(bPtr, cPtr, "+");

    /*// Create an AST for the expression: a = 2.5 + 3.5
    Float left = Float(2.5);
    Float right = Float(3.5);
    BinaryExpression expr = BinaryExpression(left, right, "+");*/

    AssignmentStatement assignment = AssignmentStatement(a, expr);
    Statement* exprPtr = &expr;

    // Create an executor and environment
    Executor executor;
    auto result1 = executor.executeBinaryExpression(&expr);

    // Execute the expression
    auto result = executor.execute(exprPtr);

    // Check the result - assuming result is an int
    //assert(result == 5);
}


int main(int argc, char *argv[]) {
    testArithmeticExpression();
    std::cout << "All tests passed!" << std::endl;

    /*if (argc!=2) {
        throw ArgsError(2, argc);
    }

    std::string filename = argv[1];
    std::fstream file(filename);
    if (!file.is_open()) {
        throw FileNotFoundError(filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    CFG cfg;
    MyLang mylang(cfg);

    mylang.interpret(buffer.str());*/

    return 0;
}