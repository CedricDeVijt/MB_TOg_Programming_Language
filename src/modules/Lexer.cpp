#include "Lexer.h"



Tokens Lexer::lex(const std::string &input) {
    Tokens tokenList;
    size_t pos = 0;


    std::regex var_regex("var");
    std::regex identifier_regex("[a-zA-Z_][a-zA-Z0-9_]*");
    std::regex equals_regex("=");
    std::regex integer_regex("\\d+");


    while (pos < input.size()) {
        std::smatch match;

        if (std::regex_search(input.begin() + pos, input.end(), match, var_regex)) {
            tokenList.push_back({TokenType::VAR,0,0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, identifier_regex)) {
            tokenList.push_back({TokenType::IDENTIFIER,0,0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, equals_regex)) {
            tokenList.push_back({TokenType::EQUALS,0,0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, integer_regex)) {
            tokenList.push_back({TokenType::INTEGER,0,0, match[0]});
        } else {
            std::cerr << "Invalid token at position " << pos << ": " << input[pos] << std::endl;
            exit(1);
        }

        pos += match.position() + match.length();
    }




    return tokenList;
}
