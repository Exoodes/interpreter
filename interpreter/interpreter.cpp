#include <fstream>
#include <interpreter/common.hpp>
#include <interpreter/lexer.hpp>
#include <iostream>
#include <sstream>

int main( int, const char** argv )
{
    std::string file_contents = get_file_contents( argv[ 1 ] );
    Lexer lexer( file_contents );
    std::vector< Token > tokens = lexer.generete_tokens();

    for ( auto& t : tokens ) {
        // std::cout << t << std::endl;
    }

    return EXIT_SUCCESS;
}
