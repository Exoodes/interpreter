#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <interpreter/common.hpp>
#include <interpreter/lexer.hpp>
#include <iostream>

namespace fs = std::filesystem;

std::vector< fs::directory_entry > get_test_files()
{
    std::vector< fs::directory_entry > out;
    for ( auto file : fs::recursive_directory_iterator( "tests/input" ) )
        if ( fs::is_regular_file( file.status() ) && file.path().extension() == ".test" )
            out.push_back( file );

    return out;
}

class FileTests : public testing::TestWithParam< fs::directory_entry > {
public:
    struct PrintToStringParamName {
        template < class ParamType >
        std::string operator()( const testing::TestParamInfo< ParamType >& info ) const
        {
            auto entry = static_cast< fs::directory_entry >( info.param );
            auto name = entry.path().filename().stem().string();
            name.erase( std::remove_if( name.begin(),
                                        name.end(),
                                        []( char c ) { return !std::isalnum( c ); } ),
                        name.end() );
            return name;
        }
    };
};


TEST_P( FileTests, Lexer )
{
    std::string file_contents = get_file_contents( GetParam().path() );
    Lexer lexer( file_contents );

    lexer.generete_tokens();
    EXPECT_FALSE( lexer.had_error );
}

TEST_P( FileTests, Grammar ) {}

INSTANTIATE_TEST_SUITE_P( FileTests,
                          FileTests,
                          testing::ValuesIn( get_test_files() ),
                          FileTests::PrintToStringParamName() );
