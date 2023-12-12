#include "MyLang.h"
#include "exceptions/FileNotFoundError.h"
#include "exceptions/ArgsError.h"
#include <fstream>
#include <sstream>


int main(int argc, char *argv[]) {
    std::string filename;
    if (argc!=2) {
        std::cout << "Didn't get correct run arguments...\n Input a filename to interpret: ";
        std::cin >> filename;
    } else {
        filename = argv[1];
    }

    std::fstream file(filename);
    if (!file.is_open()) {
        throw FileNotFoundError(filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    CFG cfg("../../src/cfg.json");
    MyLang mylang(cfg);

    mylang.interpret(buffer.str());

    return 0;
}