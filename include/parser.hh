#pragma once
#include <vector>
#include "token.hh"
#include "ast.hh"

namespace hyde {

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::vector<std::shared_ptr<Statement>> parse();

private:
    const std::vector<Token>& tokens;
    size_t current = 0;

    bool match(TokenType type);
    const Token& advance();
    const Token& peek() const;
    bool isAtEnd() const;

    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> primary();
    std::shared_ptr<Expr> binaryOp(int precedence);
    

    std::shared_ptr<Statement> statement();
    std::shared_ptr<Statement> printStatement();
    std::shared_ptr<Statement> exprStatement();
    std::shared_ptr<Statement> whetherStatement();
    std::shared_ptr<Statement> duringStatement();
    

    int getPrecedence(const Token& token) const;
};

}
