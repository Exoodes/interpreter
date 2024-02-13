#include <gtest/gtest.h>
#include <interpreter/lexer.hpp>
#include <iostream>
#include <tests/tests.helper.hpp>
#include <variant>

void check_token( Token token,
                  TokenType type,
                  token_value_t value = std::monostate{},
                  std::optional< int > line_number = std::nullopt )
{
    EXPECT_EQ( token.type, type );
    EXPECT_EQ( token.value, value );
    EXPECT_EQ( token.line, line_number.value_or( token.line ) );
}

TEST( LexerTokenizerTest, SimpleTokens )
{
    Lexer lexer( "(){},.-+;/*" );
    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 11 );

    check_token( output[ 0 ], TokenType::LEFT_PARANTHESES );
    check_token( output[ 1 ], TokenType::RIGHT_PARANTHESES );
    check_token( output[ 2 ], TokenType::LEFT_BRACKET );
    check_token( output[ 3 ], TokenType::RIGHT_BRACKET );
    check_token( output[ 4 ], TokenType::COMMA );
    check_token( output[ 5 ], TokenType::DOT );
    check_token( output[ 6 ], TokenType::MINUS );
    check_token( output[ 7 ], TokenType::PLUS );
    check_token( output[ 8 ], TokenType::SEMICOLON );
    check_token( output[ 9 ], TokenType::SLASH );
    check_token( output[ 10 ], TokenType::STAR );
}

TEST( LexerTokenizerTest, BinaryOperations )
{
    Lexer lexer( "! != = == < <= > >= | || & &&" );
    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 12 );

    check_token( output[ 0 ], TokenType::NEGATION );
    check_token( output[ 1 ], TokenType::NOT_EQUAL );
    check_token( output[ 2 ], TokenType::EQUAL );
    check_token( output[ 3 ], TokenType::EQUAL_EQUAL );
    check_token( output[ 4 ], TokenType::LESS );
    check_token( output[ 5 ], TokenType::LESS_EQUAL );
    check_token( output[ 6 ], TokenType::GREATER );
    check_token( output[ 7 ], TokenType::GREATER_EQUAL );
    check_token( output[ 8 ], TokenType::BIT_OR );
    check_token( output[ 9 ], TokenType::LOGICAL_OR );
    check_token( output[ 10 ], TokenType::BIT_AND );
    check_token( output[ 11 ], TokenType::LOGICAL_AND );
}


TEST( LexerTokenizerTest, Numbers )
{
    Lexer lexer( "1 123 99999999 -123 0.00005 123.123 99999.999 -231321.3232" );
    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 10 );

    check_token( output[ 0 ], TokenType::INTEGER, 1 );
    check_token( output[ 1 ], TokenType::INTEGER, 123 );
    check_token( output[ 2 ], TokenType::INTEGER, 99999999 );
    check_token( output[ 3 ], TokenType::MINUS );
    check_token( output[ 4 ], TokenType::INTEGER, 123 );
    check_token( output[ 5 ], TokenType::DOUBLE, 0.00005 );
    check_token( output[ 6 ], TokenType::DOUBLE, 123.123 );
    check_token( output[ 7 ], TokenType::DOUBLE, 99999.999 );
    check_token( output[ 8 ], TokenType::MINUS );
    check_token( output[ 9 ], TokenType::DOUBLE, 231321.3232 );
}

TEST( LexerTokenizerTest, Comments )
{
    Lexer lexer( "    //     1  \n"
                 "// 2 asdasd a 312321  sad !@#$%^&*( \n"
                 " {}   // 3 wqeqwe wqeqwe\n"
                 "    // 4  1231    \n"
                 "    // 5  123 dawd a   \n"
                 "    // 6     d awda \n"
                 "    // 7  1323    \n"
                 "    // 8 sda1     \n"
                 "    // 9  awdaw daw    \n"
                 "    // 10      \n"
                 "    // 11 as dadwe      \n"
                 " ()   // 12 d123123\n" );

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 4 );

    check_token( output[ 0 ], TokenType::LEFT_BRACKET, std::monostate{}, 3 );
    check_token( output[ 1 ], TokenType::RIGHT_BRACKET, std::monostate{}, 3 );
    check_token( output[ 2 ], TokenType::LEFT_PARANTHESES, std::monostate{}, 12 );
    check_token( output[ 3 ], TokenType::RIGHT_PARANTHESES, std::monostate{}, 12 );
}

TEST( LexerTokenizeStringLiteral, Empty )
{
    Lexer lexer( R"(""           ""
                    
                                        ""


                                        ""
                    "")" );

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 5 );

    check_token( output[ 0 ], TokenType::STRING, R"()", 1 );
    check_token( output[ 1 ], TokenType::STRING, R"()", 1 );
    check_token( output[ 2 ], TokenType::STRING, R"()", 3 );
    check_token( output[ 3 ], TokenType::STRING, R"()", 6 );
    check_token( output[ 4 ], TokenType::STRING, R"()", 7 );
}

TEST( LexerTokenizeStringLiteral, Blank )
{
    Lexer lexer( R"(" ""  "
                    "   "
                    "    "


                    "     ")" );

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 5 );

    check_token( output[ 0 ], TokenType::STRING, R"( )", 1 );
    check_token( output[ 1 ], TokenType::STRING, R"(  )", 1 );
    check_token( output[ 2 ], TokenType::STRING, R"(   )", 2 );
    check_token( output[ 3 ], TokenType::STRING, R"(    )", 3 );
    check_token( output[ 4 ], TokenType::STRING, R"(     )", 6 );
}

TEST( LexerTokenizeStringLiteral, Short )
{
    Lexer lexer( R"(   "abc"   " a b c "
                    )" );

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 2 );

    check_token( output[ 0 ], TokenType::STRING, R"(abc)", 1 );
    check_token( output[ 1 ], TokenType::STRING, R"( a b c )", 1 );
}


TEST( LexerTokenizeStringLiteral, Unterminated )
{
    auto check_unterminated =
    []( std::string code ) {
        NullStream error_stream;
        Lexer lexer( code, error_stream );
        lexer.generete_tokens();
        EXPECT_TRUE( lexer.had_error );
    };

    check_unterminated( R"(   "
                    )" );
    check_unterminated( R"(")" );
    check_unterminated( R"(


        ")" );
}