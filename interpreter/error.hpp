#include <format>
#include <iostream>

void show_error( int line, std::string source, std::string message, std::ostream& os )
{
    os << std::format( "[line {}] Error {}: {}", line, source, message ) << std::endl;
}