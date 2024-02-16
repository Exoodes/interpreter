#pragma once

#include <interpreter/token.hpp>
#include <iostream>

struct Visitor;

struct BaseExpr {
    virtual void accept( Visitor& ){};
};

struct BinaryExpr : public BaseExpr {
    BaseExpr l, r;
    Token token;

    BinaryExpr( BaseExpr l, Token token, BaseExpr r );
    void accept( Visitor& ) override;
};

struct LiteralExpr : public BaseExpr {
    token_value_t value;

    LiteralExpr( token_value_t value );
    void accept( Visitor& visitor ) override;
};

struct GroupingExpr : public BaseExpr {
    BaseExpr expr;

    GroupingExpr( BaseExpr expr );
    void accept( Visitor& visitor ) override;
};

struct UnaryExpr : public BaseExpr {
    BaseExpr expr;
    Token op;

    UnaryExpr( Token op, BaseExpr expr );
    void accept( Visitor& visitor ) override;
};

struct Visitor {
    virtual void visitBinaryExpr( BinaryExpr& ) = 0;
    virtual void visitLiteralExpr( LiteralExpr& ) = 0;
    virtual void visitGroupingExpr( GroupingExpr& ) = 0;
    virtual void visitUnaryExpr( UnaryExpr& ) = 0;
};