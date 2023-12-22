#include "Lexer.h"


//TODO: zin na functie als functienaam definieren
//TODO: zin na vraag: als userinput definieren

Tokens Lexer::lex(const std::string &input) {

    Tokens tokenList;
    size_t pos = 0;
    int currentLine = 0;
    int currentColumn = 0;

    auto updatePosition = [&](size_t length) {
        for (size_t i = 0; i < length; ++i) {
            if (input[pos + i] == '\n') {
                ++currentLine;
                currentColumn = 1;
            } else {
                ++currentColumn;
            }
        }
    };


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
    std::regex functie_regex("functie\\s+([a-zA-Z_][a-zA-Z0-9_]*)");
    //std::regex functieNaam_regex("functie\\s+([a-zA-Z_][a-zA-Z0-9_]*)");
    std::regex While_regex("terwijl");
    std::regex for_regex("voor");
    std::regex bool_regex("\\b(waar|fout)\\b");
    std::regex print_regex("schrijf");
    std::regex Uinput_regex("vraag:(.+)");
    //std::regex input_regex("vraag:(.+)");
    std::regex comment_regex("#\\s*(.*)");
    std::regex float_regex("([+-]?[0-9]+\\.[0-9]+)");
    std::regex limit_regex(";");
    std::regex string_regex("\"([^\"]*)\"|'([^']*)'");


    while (pos < input.size()) {
        std::smatch match;

        if (std::regex_search(input.begin() + pos, input.end(), match, var_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::VAR,currentLine,currentColumn, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, equals_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::EQUALS,currentLine,currentColumn, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, minus_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::MINUS,currentLine,currentColumn, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, comma_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::COMMA,currentLine,currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, openParen_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::OPENPAREN, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, float_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::FLOAT, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, closeParen_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::CLOSEPAREN, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, integer_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::INTEGER, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, string_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::STRING, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, plus_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::PLUS,currentLine,currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, times_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::TIMES, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, divide_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::DIVIDE, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, functie_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::FUNCTION, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, ifLoop_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::IF, currentLine, currentColumn, match[0]});
            // }else if (std::regex_search(input.begin() + pos, input.end(), match, functieNaam_regex,  std::regex_constants::match_continuous)) {
            // tokenList.push_back({TokenType::FUNCTIONNAME, 0, 0, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, elseIfLoop_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::ELSEIF, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, else_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::ELSE, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, While_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::WHILE, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, for_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::FOR, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, print_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::PRINT, currentLine, currentColumn, match[0]});
            // }else if (std::regex_search(input.begin() + pos, input.end(), match, input_regex,  std::regex_constants::match_continuous)) {
            // tokenList.push_back({TokenType::INPUT, 0, 0,match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, Uinput_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::USERINPUT, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, comment_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::COMMENT, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, greaterThan_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::GREATHERTHAN, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, LessThan_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::LESSTHAN, currentLine, currentColumn, match[0]});
        }else if (std::regex_search(input.begin() + pos, input.end(), match, bool_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::BOOL, currentLine, currentColumn, match[0]});
        } else if (std::regex_search(input.begin() + pos, input.end(), match, limit_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::LIMIT,currentLine,currentColumn, match[0]});
            ++currentLine;
            currentColumn = 0;
        } else if (std::regex_search(input.begin() + pos, input.end(), match, identifier_regex,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::IDENTIFIER,currentLine,currentColumn, match[0]});
        }else {
            std::cerr << "Invalid token at position " << pos << ": " << input[pos] << std::endl;
            exit(1);
        }
        updatePosition(match.length());
        if(currentLine != 0 and currentColumn == 1){
            currentColumn = 0;
        }
        pos += match.position() + match.length();
        while (pos < input.length() && std::isspace(input[pos])) {
            ++pos;
            ++currentColumn;
        }
    }

    Token lastElement = tokenList.back();
    Token eofToken(TokenType::EOFTOKEN, lastElement.line, lastElement.column);
    tokenList.push_back(eofToken);
    return tokenList;

}