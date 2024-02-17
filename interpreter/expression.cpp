#include <interpreter/expression.hpp>
#include <interpreter/token.hpp>
#include <iostream>

void BinaryExpr::accept( Visitor& visitor ) { visitor.visitBinaryExpr( *this ); }
BinaryExpr::BinaryExpr( BaseExprPtr l, Token token, BaseExprPtr r )
    : l( std::move( l ) )
    , r( std::move( r ) )
    , token( token )
{}


void LiteralExpr::accept( Visitor& visitor ) { visitor.visitLiteralExpr( *this ); }
LiteralExpr::LiteralExpr( token_value_t value )
    : value( value )
{}


void GroupingExpr::accept( Visitor& visitor ) { visitor.visitGroupingExpr( *this ); }
GroupingExpr::GroupingExpr( BaseExprPtr expr )
    : expr( std::move( expr ) )
{}


void UnaryExpr::accept( Visitor& visitor ) { visitor.visitUnaryExpr( *this ); }
UnaryExpr::UnaryExpr( Token op, BaseExprPtr expr )
    : expr( std::move( expr ) )
    , op( op )
{}
