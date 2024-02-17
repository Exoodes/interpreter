#include <interpreter/expression.hpp>
#include <string>

std::string get_file_contents( std::string );

struct PrintVisitor : public Visitor {
    void print( BaseExpr& expr );

    void paranthesize( std::string s, BaseExpr& expr );
    void paranthesize( std::string s, BaseExpr& expr_l, BaseExpr& expr_r );

    void visitBinaryExpr( BinaryExpr& ) override;
    void visitLiteralExpr( LiteralExpr& ) override;
    void visitGroupingExpr( GroupingExpr& ) override;
    void visitUnaryExpr( UnaryExpr& ) override;
};