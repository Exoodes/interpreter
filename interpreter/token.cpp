#include <interpreter/token.hpp>

std::ostream& operator<<( std::ostream& os, const Token& token )
{
    std::string output = std::format( "Token( type: {:18}, line: {:2}, value: {} )\n",
                                      print_type( token.type ),
                                      token.line,
                                      token.lexeme );
    return os << output;
}