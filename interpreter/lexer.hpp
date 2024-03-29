#pragma once

#include <interpreter/token.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace lexer
{


struct Reserved_words_map;

class Lexer {
    std::size_t pointer = 0;
    std::size_t start = 0;
    std::size_t token_len = 0;
    std::vector< Token > tokens;
    std::ostream& error_stream;
    int line = 1;

    void error( std::string );

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
    void add_token( TokenType type, token_value_t value );

public:
    static Reserved_words_map map;
    bool had_error = false;
    std::string source_code;

    Lexer( std::string );
    Lexer( std::string, std::ostream& );
    std::vector< Token > generete_tokens();
};


struct Reserved_words_map {
    std::map< TokenType, std::string > map_t_to_s;
    std::map< std::string, TokenType > map_s_to_t;

    void add( TokenType type, std::string str )
    {
        map_t_to_s.insert( { type, str } );
        map_s_to_t.insert( { str, type } );
    }

    std::string get( TokenType type ) { return map_t_to_s.at( type ); }
    TokenType get( std::string str )
    {
        auto it = map_s_to_t.find( str );
        if ( it == map_s_to_t.end() ) {
            return TokenType::UNKNOW;
        }

        return it->second;
    }

    Reserved_words_map()
    {
        add( TokenType::LEFT_PARANTHESES, "left_parantheses" );
        add( TokenType::RIGHT_PARANTHESES, "right_parantheses" );
        add( TokenType::LEFT_BRACKET, "left_bracket" );
        add( TokenType::RIGHT_BRACKET, "right_bracket" );
        add( TokenType::COMMA, "comma" );
        add( TokenType::DOT, "dot" );
        add( TokenType::MINUS, "minus" );
        add( TokenType::PLUS, "plus" );
        add( TokenType::SEMICOLON, "semicolon" );
        add( TokenType::SLASH, "slash" );
        add( TokenType::STAR, "star" );

        add( TokenType::NEGATION, "neagtion" );
        add( TokenType::NOT_EQUAL, "not_equal" );
        add( TokenType::EQUAL, "equal" );
        add( TokenType::EQUAL_EQUAL, "equal_equal" );
        add( TokenType::GREATER, "greater" );
        add( TokenType::GREATER_EQUAL, "greater_equal" );
        add( TokenType::LESS, "less" );
        add( TokenType::LESS_EQUAL, "less_equal" );
        add( TokenType::LOGICAL_AND, "logical_and" );
        add( TokenType::BIT_AND, "bit_aand" );
        add( TokenType::LOGICAL_OR, "logical_or" );
        add( TokenType::BIT_OR, "bit_or" );

        add( TokenType::IDENTIFIER, "identifier" );
        add( TokenType::STRING, "string" );
        add( TokenType::INTEGER, "integer" );
        add( TokenType::DOUBLE, "double" );

        add( TokenType::FN, "fn" );
        add( TokenType::FOR, "for" );
        add( TokenType::ELSE, "else" );
        add( TokenType::IF, "if" );
        add( TokenType::WHILE, "while" );
        add( TokenType::RETURN, "return" );
        add( TokenType::FALSE, "false" );
        add( TokenType::TRUE, "true" );
        add( TokenType::LET, "let" );
        add( TokenType::CLASS, "class" );
        add( TokenType::NIL, "nil" );
        add( TokenType::SUPER, "super" );
        add( TokenType::THIS, "this" );
        add( TokenType::PRINT, "print" );
        add( TokenType::EOF_T, "EOF_T" );
        add( TokenType::UNKNOW, "unknonw" );
    }
};
} // namespace lexer