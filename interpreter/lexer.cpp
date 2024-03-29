#include <cassert>
#include <interpreter/error.hpp>
#include <interpreter/lexer.hpp>
#include <interpreter/token.hpp>
#include <iostream>
#include <string>

namespace lexer
{
Reserved_words_map Lexer::map;

Lexer::Lexer( std::string source_code )
    : error_stream( std::cerr )
    , source_code( source_code )
{}

Lexer::Lexer( std::string source_code, std::ostream& error_stream )
    : error_stream( error_stream )
    , source_code( source_code )
{}

void Lexer::error( std::string message )
{
    had_error = true;
    return show_error( line, "lexing error", message, error_stream );
}


bool Lexer::is_at_end() { return pointer == source_code.length(); }

bool Lexer::match( char c )
{
    if ( is_at_end() || source_code[ pointer ] != c )
        return false;

    pointer++;
    return true;
}

char Lexer::peek( std::size_t offset )
{
    if ( pointer + offset >= source_code.size() )
        return '\0';
    return source_code[ pointer + offset ];
}

char Lexer::peek() { return peek( 0 ); }

char Lexer::advance()
{
    assert( !is_at_end() );
    char c = source_code[ pointer ];
    pointer++;
    token_len++;
    return c;
}

void Lexer::scan_number()
{
    bool is_double = false;
    while ( isdigit( peek() ) )
        advance();

    if ( peek() == '.' && isdigit( peek( 1 ) ) ) {
        is_double = true;
        advance();
    }

    while ( isdigit( peek() ) )
        advance();

    std::string lexeme = source_code.substr( start, pointer - start );

    try {
        is_double ? add_token( TokenType::DOUBLE, std::stod( lexeme ) ) :
                    add_token( TokenType::INTEGER, std::stoi( lexeme ) );
    } catch ( const std::exception& e ) {
        error( e.what() );
    }
}


void Lexer::scan_identifier()
{
    while ( isalnum( peek() ) )
        advance();

    std::string lexeme = source_code.substr( start, pointer - start );
    TokenType type = Lexer::map.get( lexeme );

    if ( type == TokenType::UNKNOW )
        type = TokenType::IDENTIFIER;

    add_token( type, lexeme );
}

void Lexer::scan_string_literal()
{
    while ( peek() != '"' && !is_at_end() ) {
        if ( peek() == '\n' )
            line++;

        advance();
    }

    if ( is_at_end() ) {
        return error( "Unterminated string literal" );
    }

    advance();

    std::string value = source_code.substr( start + 1, token_len - 2 );
    add_token( TokenType::STRING, value );
}

void Lexer::scan_comment()
{
    while ( peek() != '\n' && !is_at_end() ) {
        advance();
    }
}

void Lexer::add_token( TokenType type ) { add_token( type, std::monostate{} ); }

void Lexer::add_token( TokenType type, token_value_t value )
{
    std::string lexem = source_code.substr( start, pointer - start );
    tokens.emplace_back( type, value, lexem, line );
}

void Lexer::scan_token()
{
    char c = advance();

    if ( isspace( c ) ) {
        if ( c == '\n' )
            line++;

        return;
    }

    switch ( c ) {
        // Single-character tokens
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

        // Binary operator tokens
        case '!': add_token( match( '=' ) ? TokenType::NOT_EQUAL : TokenType::NEGATION ); break;
        case '=': add_token( match( '=' ) ? TokenType::EQUAL_EQUAL : TokenType::EQUAL ); break;
        case '<': add_token( match( '=' ) ? TokenType::LESS_EQUAL : TokenType::LESS ); break;
        case '>': add_token( match( '=' ) ? TokenType::GREATER_EQUAL : TokenType::GREATER ); break;
        case '|': add_token( match( '|' ) ? TokenType::LOGICAL_OR : TokenType::BIT_OR ); break;
        case '&': add_token( match( '&' ) ? TokenType::LOGICAL_AND : TokenType::BIT_AND ); break;
        case '/': peek() == '/' ? scan_comment() : add_token( TokenType::SLASH ); break;

        // Longer tokens
        case '"': scan_string_literal(); break;
        default:
            if ( isdigit( c ) )
                scan_number();
            else if ( isalpha( c ) )
                scan_identifier();
            else
                return error( "Unknown character" );

            break;
    }
}

std::vector< Token > Lexer::generete_tokens()
{
    while ( !is_at_end() ) {
        start = pointer;
        token_len = 0;
        scan_token();
    }

    return tokens;
}

} // namespace lexer