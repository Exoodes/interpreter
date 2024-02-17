#include <interpreter/lexer.hpp>
#include <interpreter/token.hpp>
#include <iomanip>
#include <variant>

template < class... Ts >
struct overload : Ts... {
    using Ts::operator()...;
};

std::ostream& operator<<( std::ostream& os, const Token& token )
{
    os << std::format( "Token( type: {:18}, line: {:2}, lexeme: \"{}\"",
                       lexer::Lexer::map.get( token.type ),
                       token.line,
                       token.lexeme );


    std::visit( overload{ [ & ]( int ) { os << ", type: int"; },
                          [ & ]( double ) { os << ", type: double"; },
                          [ & ]( std::string ) { os << ", type: string"; },
                          [ & ]( std::monostate ) {} },
                token.value );

    return os << " )";
}