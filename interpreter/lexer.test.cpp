#include <gtest/gtest.h>
#include <interpreter/lexer.hpp>

TEST( LexerTest, SimpleTokens )
{
    Lexer lexer( "(){},.-+;/*" );
    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 11 );

    EXPECT_EQ( output[ 0 ].type, TokenType::LEFT_PARANTHESES );
    EXPECT_EQ( output[ 1 ].type, TokenType::RIGHT_PARANTHESES );
    EXPECT_EQ( output[ 2 ].type, TokenType::LEFT_BRACKET );
    EXPECT_EQ( output[ 3 ].type, TokenType::RIGHT_BRACKET );
    EXPECT_EQ( output[ 4 ].type, TokenType::COMMA );
    EXPECT_EQ( output[ 5 ].type, TokenType::DOT );
    EXPECT_EQ( output[ 6 ].type, TokenType::MINUS );
    EXPECT_EQ( output[ 7 ].type, TokenType::PLUS );
    EXPECT_EQ( output[ 8 ].type, TokenType::SEMICOLON );
    EXPECT_EQ( output[ 9 ].type, TokenType::SLASH );
    EXPECT_EQ( output[ 10 ].type, TokenType::STAR );
}

TEST( LexerTest, BinaryOperations )
{
    Lexer lexer( "! != = == < <= > >= | || & &&" );
    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 12 );

    EXPECT_EQ( output[ 0 ].type, TokenType::NEGATION );
    EXPECT_EQ( output[ 1 ].type, TokenType::NOT_EQUAL );
    EXPECT_EQ( output[ 2 ].type, TokenType::EQUAL );
    EXPECT_EQ( output[ 3 ].type, TokenType::EQUAL_EQUAL );
    EXPECT_EQ( output[ 4 ].type, TokenType::LESS );
    EXPECT_EQ( output[ 5 ].type, TokenType::LESS_EQUAL );
    EXPECT_EQ( output[ 6 ].type, TokenType::GREATER );
    EXPECT_EQ( output[ 7 ].type, TokenType::GREATER_EQUAL );
    EXPECT_EQ( output[ 8 ].type, TokenType::BIT_OR );
    EXPECT_EQ( output[ 9 ].type, TokenType::LOGICAL_OR );
    EXPECT_EQ( output[ 10 ].type, TokenType::BIT_AND );
    EXPECT_EQ( output[ 11 ].type, TokenType::LOGICAL_AND );
}

TEST( LexerTest, Numbers )
{
    Lexer lexer( "1 123 99999999 -123 0.00005 123.123 99999.999 -231321.3232" );
    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 10 );

    EXPECT_EQ( output[ 0 ].type, TokenType::INTEGER );
    EXPECT_EQ( std::get< int >( output[ 0 ].value ), 1 );
    EXPECT_EQ( output[ 1 ].type, TokenType::INTEGER );
    EXPECT_EQ( std::get< int >( output[ 1 ].value ), 123 );
    EXPECT_EQ( output[ 2 ].type, TokenType::INTEGER );
    EXPECT_EQ( std::get< int >( output[ 2 ].value ), 99999999 );
    EXPECT_EQ( output[ 3 ].type, TokenType::MINUS );
    EXPECT_EQ( output[ 4 ].type, TokenType::INTEGER );
    EXPECT_EQ( std::get< int >( output[ 4 ].value ), 123 );
    EXPECT_EQ( output[ 5 ].type, TokenType::DOUBLE );
    EXPECT_EQ( std::get< double >( output[ 5 ].value ), 0.00005 );
    EXPECT_EQ( output[ 6 ].type, TokenType::DOUBLE );
    EXPECT_EQ( std::get< double >( output[ 6 ].value ), 123.123 );
    EXPECT_EQ( output[ 7 ].type, TokenType::DOUBLE );
    EXPECT_EQ( std::get< double >( output[ 7 ].value ), 99999.999 );
    EXPECT_EQ( output[ 8 ].type, TokenType::MINUS );
    EXPECT_EQ( output[ 9 ].type, TokenType::DOUBLE );
    EXPECT_EQ( std::get< double >( output[ 9 ].value ), 231321.3232 );
}