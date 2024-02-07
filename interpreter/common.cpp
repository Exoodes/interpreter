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
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        default:
            return "default";
            // default: assert( false );
    }
}
