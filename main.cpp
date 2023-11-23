#include "./src/MyLang.h"
#include "./src/exceptions/FileNotFoundError.h"
#include "./src/exceptions/ArgsError.h"
#include <fstream>
#include <sstream>


int main(int argc, char *argv[]) {
    if (argc!=1) {
        throw ArgsError(1, argc);
    }

    std::string filename = argv[0];
    std::fstream file(filename);
    if (!file.is_open()) {
        throw FileNotFoundError(filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    CFG cfg;
    MyLang mylang(cfg);

    mylang.interpret(buffer.str());

    return 0;
}