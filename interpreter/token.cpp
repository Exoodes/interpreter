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
    os << std::format( "Token( type: {:18}, line: {:2}, lexeme: {}",
                       Lexer::map.get( token.type ),
                       token.line,
                       token.lexeme );


    std::visit( overload{ [ & ]( int i ) { os << std::format( ", int: {}", i ); },
                          [ & ]( double d ) { os << std::format( ", double: {}", d ); },
                          [ & ]( std::string s ) { os << std::format( ", string: \"{}\"", s ); },
                          [ & ]( std::monostate ) {} },
                token.value );

    return os << " )\n";
}