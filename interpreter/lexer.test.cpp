#include <gtest/gtest.h>
#include <interpreter/lexer.hpp>

TEST( LexerTest, Match )
{
    Lexer lexer( "abcdefgh" );
    auto output = lexer.generete_tokens();
    EXPECT_EQ( output.size(), 1 );
}