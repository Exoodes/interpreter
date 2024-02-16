#include <interpreter/expression.hpp>
#include <string>

std::string get_file_contents( std::string );

struct PrintVisitor : public Visitor {
    void print( BaseExpr& expr );
    void paranthesize( BaseExpr& expr );

    void visitBinaryExpr( BinaryExpr& ) override;
    void visitLiteralExpr( LiteralExpr& ) override;
    void visitGroupingExpr( GroupingExpr& ) override;
    void visitUnaryExpr( UnaryExpr& ) override;
};