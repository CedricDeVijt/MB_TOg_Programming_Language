#include "Lexer.h"


//TODO: zin na functie als functienaam definieren
//TODO: zin na vraag: als userinput definieren
//TODO: string identificeren
//TODO: FLOAT

Tokens Lexer::lex(const std::string &input) {

    Tokens tokenList;
    size_t pos = 0;


    std::regex var_regex("var");
    std::regex identifier_regex("[a-zA-Z_][a-zA-Z0-9_]*");
    std::regex equals_regex("=");
    std::regex plus_regex("\\+");
    std::regex minus_regex("-");
    std::regex comma_regex(",");
    std::regex greaterThan_regex(">");
    std::regex LessThan_regex("<");
    std::regex openParen_regex("\\(");
    std::regex closeParen_regex("\\)");
    std::regex integer_regex("\\d+");
    std::regex times_regex("\\*");
    std::regex divide_regex("/");
    std::regex ifLoop_regex("als");
    std::regex elseIfLoop_regex("anders als");
    std::regex else_regex("anders");
    std::regex functie_regex("functie");
    // std::regex functieNaam_regex("functie\\s+([a-zA-Z_][a-zA-Z0-9_]*)");
    std::regex While_regex("terwijl");
    std::regex for_regex("voor");
    std::regex bool_regex("\\b(waar|fout)\\b");
    std::regex print_regex("schrijf");
    std::regex Uinput_regex("vraag:");
    //std::regex input_regex("vraag: .....");
    std::regex comment_regex("#\\s*(.*)");
    // std::regex float_regex("^\\d*\\.?\\d*$");



    while (pos < input.size()) {
        std::smatch match;

        if (std::regex_search(input.begin() + pos, input.end(), match, var_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::VAR,0,0, match[0]});
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
        }else if (std::regex_search(input.begin() + pos, input.end(), match, functie_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::FUNCTION, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, ifLoop_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::IF, 0, 0, match[0]});
            // }else if (std::regex_search(input.begin() + pos, input.end(), match, functieNaam_regex,  std::regex_constants::match_continuous)) {
            // tokenList.push_back({TokenType::FUNCTIONNAME, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, elseIfLoop_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::ELSEIF, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, else_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::ELSE, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, While_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::WHILE, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, for_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::FOR, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, print_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::PRINT, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, Uinput_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::USERINPUT, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, comment_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::COMMENT, 0, 0, match[0]});
            //}else if (std::regex_search(input.begin() + pos, input.end(), match, float_regex,  std::regex_constants::match_continuous)) {
            //tokenList.push_back({TokenType::FLOAT, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, greaterThan_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::GREATHERTHAN, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, LessThan_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::LESSTHAN, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, bool_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::BOOL, 0, 0, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, identifier_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::IDENTIFIER,0,0, match[0]});




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
