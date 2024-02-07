#pragma once

#include <cassert>
#include <format>
#include <ostream>
#include <string>

enum TokenType {
    // Single-character tokens.
    LEFT_PARANTHESES,
    RIGHT_PARANTHESES,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,
    EOF_T
};

std::string print_type( TokenType type )
{
    switch ( type ) {
        case LEFT_PARANTHESES: return "LEFT_PARANTHESES";
        case RIGHT_PARANTHESES: return "RIGHT_PARANTHESES";
        case LEFT_BRACKET: return "LEFT_BRACKET";
        case RIGHT_BRACKET: return "RIGHT_BRACKET";
        case COMMA: return "COMMA";
        case DOT: return "DOT";
        case MINUS: return "MINUS";
        case SEMICOLON: return "SEMICOLON";
        case STAR: return "STAR";
        default: assert( false );
    }
}

struct Token {
    TokenType type;
    std::string lexeme;

    int line;

    friend std::ostream& operator<<( std::ostream& os, const Token& token )
    {
        std::string out =
        std::format( "Token( type: {}, line: {} )\n", print_type( token.type ), token.line );
        return os << out;
    }
};