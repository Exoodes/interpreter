#include <fstream>
#include <interpreter/lexer.hpp>
#include <iostream>
#include <sstream>

int main( int, const char** argv )
{
    std::ifstream input_file( argv[ 1 ] );
    std::stringstream buffer;
    buffer << input_file.rdbuf();

    Lexer lexer( buffer.str() );
    std::vector< Token > tokens = lexer.generete_tokens();

    for ( auto& t : tokens ) {
        std::cout << t << std::endl;
    }

    return EXIT_SUCCESS;
}
