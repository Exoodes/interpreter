#include <format>
#include <iostream>

void show_error( int line, std::string source, std::string message )
{
    std::cerr << std::format( "[line {}] Error {}: {}", line, source, message ) << std::endl;
}