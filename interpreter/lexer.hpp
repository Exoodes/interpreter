#pragma once

#include <interpreter/token.hpp>
#include <string>
#include <vector>

class Lexer {
    std::size_t pointer = 0;
    std::size_t start = 0;
    std::vector< Token > tokens;
    int line = 1;

    bool match( char c );
    char peek();
    char peek( std::size_t );
    bool is_at_end();
    char advance();
    void scan_token();
    void scan_comment();
    void scan_string_literal();
    void scan_number();
    void scan_identifier();
    void add_token( TokenType type );
    void add_token( TokenType type, std::string value );

public:
    std::string source_code;

    Lexer( std::string );
    std::vector< Token > generete_tokens();
};