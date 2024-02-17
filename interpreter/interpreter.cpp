#include <fstream>
#include <interpreter/common.hpp>
#include <interpreter/expression.hpp>
#include <interpreter/lexer.hpp>
#include <iostream>
#include <sstream>

int main( int, const char** argv )
{
    std::string file_contents = get_file_contents( argv[ 1 ] );
    lexer::Lexer lexer( file_contents );
    std::vector< Token > tokens = lexer.generete_tokens();

    BaseExprPtr expr =
    make_expr< BinaryExpr >( make_expr< LiteralExpr >( std::monostate{} ),
                             Token( TokenType::PLUS, std::monostate{}, "+", 1 ),
                             make_expr< UnaryExpr >( Token( TokenType::MINUS, std::monostate{}, "-", 1 ),
                                                     make_expr< LiteralExpr >( 12 ) ) );
    PrintVisitor().print( *expr );

    return EXIT_SUCCESS;
}
