#include <gtest/gtest.h>
#include <interpreter/lexer.hpp>
#include <iostream>
#include <tests/tests.helper.hpp>

int main( int argc, char** argv )
{
    ::testing::InitGoogleTest( &argc, argv );
    if ( RUN_ALL_TESTS() )
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}