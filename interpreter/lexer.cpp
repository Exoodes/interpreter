#include <cassert>
#include <interpreter/lexer.hpp>
#include <interpreter/token.hpp>
#include <iostream>

Lexer::Lexer( std::string source_code )
    : source_code( source_code )
{}

bool Lexer::is_at_end() { return pointer == source_code.length(); }

char Lexer::advance()
{
    assert( !is_at_end() );
    char c = source_code[ pointer ];
    pointer++;
    return c;
}

void Lexer::add_token( TokenType type ) { tokens.emplace_back( type, "", line ); }

void Lexer::scan_token()
{
    char c = advance();

    if ( isblank( c ) ) {
        return;
    }

    switch ( c ) {
        // Single-character tokens.
        case '(': add_token( LEFT_PARANTHESES ); break;
        case ')': add_token( RIGHT_PARANTHESES ); break;
        case '{': add_token( LEFT_BRACKET ); break;
        case '}': add_token( RIGHT_BRACKET ); break;
        case ',': add_token( COMMA ); break;
        case '.': add_token( DOT ); break;
        case '-': add_token( MINUS ); break;
        case '+': add_token( PLUS ); break;
        case ';': add_token( SEMICOLON ); break;
        case '*': add_token( STAR ); break;

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
