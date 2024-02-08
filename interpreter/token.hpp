#pragma once

#include <format>
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
    LOGICAL_AND,
    BIT_AND,
    LOGICAL_OR,
    BIT_OR,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    FN,
    FOR,
    ELSE,
    IF,
    WHILE,
    RETURN,
    FALSE,
    TRUE,

    AND,
    CLASS,
    NIL,
    OR,
    PRINT,
    SUPER,
    THIS,
    VAR,
    EOF_T,

    UNKNOW
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    friend std::ostream& operator<<( std::ostream& os, const Token& token );

    Token( TokenType type, std::string lexeme, int line )
        : type( type )
        , lexeme( lexeme )
        , line( line )
    {}
};