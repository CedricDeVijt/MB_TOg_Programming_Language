#include "Lexer.h"



Tokens Lexer::lex(const std::string &input) {

    Tokens tokenList;
    size_t pos = 0;


    std::regex var_regex("var");
    std::regex identifier_regex("[a-zA-Z_][a-zA-Z0-9_]*");
    std::regex equals_regex("=");
    std::regex plus_regex("\\+");
    std::regex minus_regex("-");
    std::regex comma_regex(",");
    std::regex openParen_regex("\\(");
    std::regex closeParen_regex("\\)");
    std::regex integer_regex("\\d+");
    std::regex times_regex("\\*");
    std::regex divide_regex("/");

    while (pos < input.size()) {
        std::smatch match;

        if (std::regex_search(input.begin() + pos, input.end(), match, var_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::VAR,0,0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, identifier_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::IDENTIFIER,0,0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, equals_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::EQUALS,0,0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, minus_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::MINUS,0,0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, comma_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::COMMA,0,0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, openParen_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::OPENPAREN, 0, 0 + 1, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, closeParen_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::CLOSEPAREN, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, integer_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::INTEGER, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, plus_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::PLUS,0,0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, times_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::TIMES, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, divide_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::DIVIDE, 0, 0, match[0]});
        }else {
            std::cerr << "Invalid token at position " << pos << ": " << input[pos] << std::endl;
            exit(1);
        }

        pos += match.position() + match.length();
        while (pos < input.length() && std::isspace(input[pos])) {
            ++pos;
        }
    }


    return tokenList;

}