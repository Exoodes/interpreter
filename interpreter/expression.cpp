#include <interpreter/expression.hpp>
#include <interpreter/token.hpp>
#include <iostream>

void BinaryExpr::accept( Visitor& visitor ) { visitor.visitBinaryExpr( *this ); }
BinaryExpr::BinaryExpr( BaseExpr l, Token token, BaseExpr r )
    : l( l )
    , r( r )
    , token( token )
{}


void LiteralExpr::accept( Visitor& visitor ) { visitor.visitLiteralExpr( *this ); }
LiteralExpr::LiteralExpr( token_value_t value )
    : value( value )
{}


void GroupingExpr::accept( Visitor& visitor ) { visitor.visitGroupingExpr( *this ); }
GroupingExpr::GroupingExpr( BaseExpr expr )
    : expr( expr )
{}


void UnaryExpr::accept( Visitor& visitor ) { visitor.visitUnaryExpr( *this ); }
UnaryExpr::UnaryExpr( Token op, BaseExpr expr )
    : expr( expr )
    , op( op )
{}
