#pragma once

#include <interpreter/token.hpp>
#include <string>
#include <vector>

class Lexer {
    std::size_t pointer = 0;
    std::vector< Token > tokens;
    int line = 1;

    char peek();
    bool is_at_end();
    char advance();
    void scan_token();
    void scan_comment();
    void add_token( TokenType type );

public:
    std::string source_code;

    Lexer( std::string );
    std::vector< Token > generete_tokens();
};