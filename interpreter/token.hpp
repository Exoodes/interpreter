#pragma once

#include <format>
#include <interpreter/common.hpp>
#include <ostream>
#include <string>

enum class TokenType {
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
    NEGATION,
    NOT_EQUAL,
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

struct Token {
    TokenType type;
    std::string lexeme;

    int line;

    friend std::ostream& operator<<( std::ostream& os, const Token& token )
    {
        return os << std::format( "Token( type: {}, line: {} )\n", print_type( token.type ), token.line );
    }
};