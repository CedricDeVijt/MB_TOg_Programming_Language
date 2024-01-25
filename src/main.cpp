#include "MyLang.h"
#include "exceptions/FileNotFoundError.h"
#include "exceptions/ArgsError.h"
#include <fstream>
#include <sstream>


int main(int argc, char *argv[]) {

    std::string filename = "../../data/input/Eenvoudige Rekenkunde en Variabelen.txt";
    /*if (argc!=2) {
        std::cout << "Didn't get correct run arguments...\n Input a filename to interpret: ";
        std::cin >> filename; // example: "../../data/input/Rekenmachine.txt"
    } else {
        filename = argv[1];
    }*/

    std::fstream file(filename);
    if (!file.is_open()) {
        throw FileNotFoundError(filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    MyLang::interpret(buffer.str(), "../../data/LRParserTable.json");

    /*
    /*std::string input = "var x = (5 + 2)";
    Tokens tokens = Lexer::lex(input);
    for(const Token& t: tokens){
        std::cout << t << std::endl;

    }*/

    file.close();

    return 0;
}