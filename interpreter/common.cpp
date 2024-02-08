#include <cassert>
#include <interpreter/common.hpp>
#include <interpreter/token.hpp>
#include <string>

std::string print_type( const TokenType& type )
{
    switch ( type ) {
        case TokenType::LEFT_PARANTHESES: return "LEFT_PARANTHESES";
        case TokenType::RIGHT_PARANTHESES: return "RIGHT_PARANTHESES";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";

        case TokenType::NEGATION: return "NEGATION";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";

        // Literals
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";

        // Keywords
        case TokenType::AND: return "AND";
        case TokenType::CLASS: return "CLASS";
        case TokenType::ELSE: return "ELSE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::FN: return "FN";
        case TokenType::FOR: return "FOR";
        case TokenType::IF: return "IF";
        case TokenType::NIL: return "NIL";
        case TokenType::OR: return "OR";
        case TokenType::RETURN: return "RETURN";
        case TokenType::TRUE: return "TRUE";
        case TokenType::VAR: return "VAR";
        case TokenType::WHILE: return "WHILE";

        default:
            return "default";
            // default: assert( false );
    }
}
