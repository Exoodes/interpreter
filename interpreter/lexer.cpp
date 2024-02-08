#include <cassert>
#include <interpreter/lexer.hpp>
#include <interpreter/token.hpp>
#include <iostream>

Lexer::Lexer( std::string source_code )
    : source_code( source_code )
{}

bool Lexer::is_at_end() { return pointer == source_code.length(); }

bool Lexer::match( char c )
{
    if ( is_at_end() || source_code[ pointer ] != c )
        return false;

    pointer++;
    return true;
}

char Lexer::peek() { return is_at_end() ? '\n' : source_code[ pointer ]; }

char Lexer::advance()
{
    assert( !is_at_end() );
    char c = source_code[ pointer ];
    pointer++;
    return c;
}

void Lexer::scan_comment()
{
    while ( peek() != '\n' && !is_at_end() ) {
        advance();
    }
}

void Lexer::add_token( TokenType type ) { tokens.emplace_back( type, "", line ); }

void Lexer::scan_token()
{
    char c = advance();

    if ( isspace( c ) ) {
        if ( c == '\n' )
            line++;

        return;
    }

    switch ( c ) {
        // Single-character tokens.
        case '(': add_token( TokenType::LEFT_PARANTHESES ); break;
        case ')': add_token( TokenType::RIGHT_PARANTHESES ); break;
        case '{': add_token( TokenType::LEFT_BRACKET ); break;
        case '}': add_token( TokenType::RIGHT_BRACKET ); break;
        case ',': add_token( TokenType::COMMA ); break;
        case '.': add_token( TokenType::DOT ); break;
        case '-': add_token( TokenType::MINUS ); break;
        case '+': add_token( TokenType::PLUS ); break;
        case ';': add_token( TokenType::SEMICOLON ); break;
        case '*': add_token( TokenType::STAR ); break;

        // Binary operators
        case '!': add_token( match( '=' ) ? TokenType::NOT_EQUAL : TokenType::NEGATION ); break;
        case '=': add_token( match( '=' ) ? TokenType::EQUAL_EQUAL : TokenType::EQUAL ); break;
        case '<': add_token( match( '=' ) ? TokenType::LESS_EQUAL : TokenType::LESS ); break;
        case '>': add_token( match( '=' ) ? TokenType::GREATER_EQUAL : TokenType::GREATER ); break;
        case '/': peek() == '/' ? scan_comment() : add_token( TokenType::SLASH ); break;

        default: break;
    }
}

std::vector< Token > Lexer::generete_tokens()
{
    while ( !is_at_end() ) {
        scan_token();
    }

    return tokens;
}
