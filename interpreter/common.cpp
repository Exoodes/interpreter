#include <fstream>
#include <sstream>
#include <string>

std::string get_file_contents( std::string path )
{
    std::ifstream input_file( path );
    std::stringstream buffer;
    buffer << input_file.rdbuf();

    return buffer.str();
}