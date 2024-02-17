#pragma once

#include <interpreter/token.hpp>
#include <iostream>
#include <memory>

struct BaseExpr;
using BaseExprPtr = std::unique_ptr< BaseExpr >;

template < typename T, typename... Args >
BaseExprPtr make_expr( Args... args )
{
    return std::make_unique< T >( std::forward< Args >( args )... );
}

struct Visitor;

struct BaseExpr {
    virtual void accept( Visitor& ){};
};

struct BinaryExpr : public BaseExpr {
    BaseExprPtr l, r;
    Token token;

    BinaryExpr( BaseExprPtr l, Token token, BaseExprPtr r );
    void accept( Visitor& ) override;
};

struct LiteralExpr : public BaseExpr {
    token_value_t value;

    LiteralExpr( token_value_t value );
    void accept( Visitor& visitor ) override;
};

struct GroupingExpr : public BaseExpr {
    BaseExprPtr expr;

    GroupingExpr( BaseExprPtr expr );
    void accept( Visitor& visitor ) override;
};

struct UnaryExpr : public BaseExpr {
    BaseExprPtr expr;
    Token op;

    UnaryExpr( Token op, BaseExprPtr expr );
    void accept( Visitor& visitor ) override;
};

struct Visitor {
    virtual void visitBinaryExpr( BinaryExpr& ) = 0;
    virtual void visitLiteralExpr( LiteralExpr& ) = 0;
    virtual void visitGroupingExpr( GroupingExpr& ) = 0;
    virtual void visitUnaryExpr( UnaryExpr& ) = 0;
};