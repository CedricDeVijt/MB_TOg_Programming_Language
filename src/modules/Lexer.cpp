#include "Lexer.h"


//TODO: zin na functie als functienaam definieren
//TODO: zin na vraag: als userinput definieren

/*
Tokens Lexer::lex(const std::string &input) {


    Tokens tokens;
    int line = 1, column = 1;

    for (size_t i = 0; i < input.length(); i++) {
        char currentChar = input[i];

        // Newline handling
        if (currentChar == '\n') {
            line++;
            column = 1;
            continue;
        }

        // Skip whitespace but count columns
        if (isspace(currentChar)) {
            column++;
            continue;
        }

        // Skip comments
        if (currentChar == '#' && column == 1) {
            while (i < input.length() && input[i] != '\n') {
                i++;
            }
            continue;
        }

        // Handling string literals
        if (currentChar == '"') {
            std::string value;
            size_t startColumn = column;
            i++; // Skip the opening quotation mark
            while (i < input.length() && input[i] != '"') {
                // Handle escape sequences if your language supports them
                if (input[i] == '\\' && i + 1 < input.length()) {
                    // Example: Handle escaped quotation mark
                    if (input[i + 1] == '"') {
                        i++; // Skip the escape character
                    }
                }
                value += input[i];
                i++;
            }

            if (i < input.length() && input[i] == '"') {
                // Successfully found the closing quotation mark
                tokens.push_back(Token(TokenType::STRING, line, startColumn, value));
                column = startColumn + value.length() + 2; // +2 for the opening and closing quotes
            } else {
                // Handle error: string not closed
                // You might want to add error handling logic here
            }
            continue;
        }

        // Tokenize keywords and identifiers
        // (For simplicity, only handling 'functie' and 'geef terug' and defaulting others to IDENTIFIER)
        if (isalpha(currentChar)) {
            std::string value;
            int startColumn = column;
            do {
                value += currentChar;
                currentChar = input[++i];
            } while (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_');
            i--; // Adjust for the extra increment

            if (value == "functie") {
                tokens.push_back(Token(TokenType::FUNCTION, line, column, value));
            } else if (value == "geef") {
                // Peek ahead to check if the next word is 'terug'
                std::string nextWord;
                size_t j = i + 1;
                while (j < input.length() && isspace(input[j])) j++; // Skip spaces

                while (j < input.length() && isalpha(input[j])) {
                    nextWord += input[j];
                    j++;
                }

                if (nextWord == "terug") {
                    i = j - 1; // Update the main loop index
                    column += (j - startColumn);
                    tokens.push_back(Token(TokenType::RETURN, line, startColumn, "geef terug"));
                    continue;
                }
            } else {
                // Handle other keywords and identifiers here
                tokens.push_back(Token(TokenType::IDENTIFIER, line, column, value));
            }


            column += value.length();
            continue;
        }

        // Tokenize operators and symbols
        // (For simplicity, only handling a few)
        switch (currentChar) {
            case '+':
                tokens.push_back(Token(TokenType::PLUS, line, column, "+"));
                break;
            case '(':
                tokens.push_back(Token(TokenType::OPENPAREN, line, column, "("));
                break;
            case ')':
                tokens.push_back(Token(TokenType::CLOSEPAREN, line, column, ")"));
                break;
            case '{':
                tokens.push_back(Token(TokenType::OPENBODY, line, column, "{"));
                break;
            case '}':
                tokens.push_back(Token(TokenType::CLOSEBODY, line, column, "}"));
                break;
            default:
                // Unrecognized character handling
                break;
        }
        column++;
    }

    // Add an EOF token at the end
    tokens.push_back(Token(TokenType::EOFTOKEN, line, column));

    return tokens;
}
     */

Tokens Lexer::lex(const std::string &input) {

    Tokens tokenList;
    size_t pos = 0;
    int currentLine = 0;
    int currentColumn = 0;

    auto updatePosition = [&](size_t length) {
        for (size_t i = 0; i < length; ++i) {
            if (input[pos + i] == '\n') {
                ++currentLine;
                currentColumn = 0;
                tokenList.pop_back();
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
    std::regex open_body("{");
    std::regex close_body("}");
    std::regex Return("geef terug");


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
        }else if (std::regex_search(input.begin() + pos, input.end(), match, open_body,  std::regex_constants::match_continuous)) {
             tokenList.push_back({TokenType::OPENBODY, currentLine, currentColumn, match[0]});
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
        }else if (std::regex_search(input.begin() + pos, input.end(), match, close_body,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::CLOSEBODY, currentLine, currentColumn,match[0]});
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
        }else if (std::regex_search(input.begin() + pos, input.end(), match, Return,  std::regex_constants::match_continuous)) {
            tokenList.push_back({TokenType::RETURN, currentLine, currentColumn, match[0]});
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