#include <gtest/gtest.h>
#include <interpreter/lexer.hpp>
#include <iostream>

int main( int argc, char** argv )
{
    ::testing::InitGoogleTest( &argc, argv );
    std::cout << "Running test" << std::endl;
    int ret{ RUN_ALL_TESTS() };
    if ( !ret )
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}