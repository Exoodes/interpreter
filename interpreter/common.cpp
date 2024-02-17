#include <fstream>
#include <interpreter/common.hpp>
#include <interpreter/expression.hpp>
#include <iostream>
#include <sstream>
#include <string>

template < class... Ts >
struct overload : Ts... {
    using Ts::operator()...;
};

std::string get_file_contents( std::string path )
{
    std::ifstream input_file( path );
    std::stringstream buffer;
    buffer << input_file.rdbuf();

    return buffer.str();
}

void PrintVisitor::print( BaseExpr& expr )
{
    expr.accept( *this );
    std::cout << std::endl;
}

void PrintVisitor::visitBinaryExpr( BinaryExpr& expr )
{
    std::cout << "( " << expr.token.lexeme << " ";
    expr.l->accept( *this );
    std::cout << " ";
    expr.r->accept( *this );
    std::cout << ")";
}

void PrintVisitor::visitLiteralExpr( LiteralExpr& expr )
{
    std::visit( overload{ [ & ]( int i ) { std::cout << i; },
                          [ & ]( double d ) { std::cout << d; },
                          [ & ]( std::string s ) { std::cout << s; },
                          [ & ]( std::monostate ) { std::cout << "nil"; } },
                expr.value );
}

void PrintVisitor::visitGroupingExpr( GroupingExpr& expr )
{
    std::cout << "( group ";
    expr.expr->accept( *this );
    std::cout << " )";
}

void PrintVisitor::visitUnaryExpr( UnaryExpr& expr )
{
    std::cout << "( " << expr.op.lexeme << " ";
    expr.expr->accept( *this );
    std::cout << " )";
}
