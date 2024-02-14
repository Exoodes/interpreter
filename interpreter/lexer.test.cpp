#include <gtest/gtest.h>
#include <interpreter/lexer.hpp>
#include <iostream>
#include <limits>
#include <ranges>
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

void check_error( std::string code )
{
    NullStream error_stream;
    Lexer lexer( code, error_stream );
    lexer.generete_tokens();
    EXPECT_TRUE( lexer.had_error );
}

TEST( LexerTokenizeOneCharacterTokens, Simple )
{
    Lexer lexer( "(){},.-+;/*" );

    auto types = { TokenType::LEFT_PARANTHESES,
                   TokenType::RIGHT_PARANTHESES,
                   TokenType::LEFT_BRACKET,
                   TokenType::RIGHT_BRACKET,
                   TokenType::COMMA,
                   TokenType::DOT,
                   TokenType::MINUS,
                   TokenType::PLUS,
                   TokenType::SEMICOLON,
                   TokenType::SLASH,
                   TokenType::STAR };

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), types.size() );

    for ( auto const [ index, token_type ] : std::views::enumerate( types ) ) {
        check_token( output[ index ], token_type );
    }
}

TEST( LexerTokenizeBinaryOperations, Simple )
{
    Lexer lexer( "! != = == < <= > >= | || & &&" );

    auto types = { TokenType::NEGATION,    TokenType::NOT_EQUAL,     TokenType::EQUAL,
                   TokenType::EQUAL_EQUAL, TokenType::LESS,          TokenType::LESS_EQUAL,
                   TokenType::GREATER,     TokenType::GREATER_EQUAL, TokenType::BIT_OR,
                   TokenType::LOGICAL_OR,  TokenType::BIT_AND,       TokenType::LOGICAL_AND };

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), types.size() );

    for ( auto const [ index, token_type ] : std::views::enumerate( types ) ) {
        check_token( output[ index ], token_type );
    }
}

TEST( LexerTokenizeBinaryOperations, Advanced )
{
    Lexer lexer( R"( =
    = < =
    &&&

                    )" );

    auto types = { TokenType::EQUAL, TokenType::EQUAL,       TokenType::LESS,
                   TokenType::EQUAL, TokenType::LOGICAL_AND, TokenType::BIT_AND };

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), types.size() );

    for ( auto const [ index, token_type ] : std::views::enumerate( types ) ) {
        check_token( output[ index ], token_type );
    }
}


TEST( LexerTokenizeNumbers, Simple )
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

TEST( LexerTokenizeNumbers, Overflow ) { check_error( "2147483648" ); }

TEST( LexerTokenizeComments, Simple )
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

TEST( LexerTokenizeStringLiterals, Empty )
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

TEST( LexerTokenizeStringLiterals, Blank )
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

TEST( LexerTokenizeStringLiterals, Short )
{
    Lexer lexer( R"(   "abc"   " a b c "
                    )" );

    auto output = lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
    EXPECT_EQ( output.size(), 2 );

    check_token( output[ 0 ], TokenType::STRING, R"(abc)", 1 );
    check_token( output[ 1 ], TokenType::STRING, R"( a b c )", 1 );
}


TEST( LexerTokenizeStringLiterals, Unterminated )
{
    check_error( R"(   "
                    )" );
    check_error( R"(")" );
    check_error( R"(


        ")" );
}

TEST( LexerTokenizeIdentifiers, ReservedWords ) {}
TEST( LexerTokenizeIdentifiers, Identfiers ) {}
TEST( LexerTokenizeIdentifiers, Mixed ) {}
TEST( LexerTokenizeIdentifiers, InComments ) {}


// TEST() {}