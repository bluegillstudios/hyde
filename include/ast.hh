#pragma once
#include <string>
#include <memory>
#include <vector>

namespace hyde {

struct Expr {
    virtual ~Expr() = default;
};

struct AssignExpr : Expr {
    std::string name;
    std::shared_ptr<Expr> value;

    AssignExpr(std::string name, std::shared_ptr<Expr> value)
        : name(std::move(name)), value(std::move(value)) {}
};

struct NumberExpr : Expr {
    double value;
    explicit NumberExpr(double val) : value(val) {}
};

struct VariableExpr : Expr {
    std::string name;
    explicit VariableExpr(const std::string& n) : name(n) {}
};

struct BinaryExpr : Expr {
    std::string op;
    std::shared_ptr<Expr> left, right;
    BinaryExpr(std::string o, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r)
        : op(std::move(o)), left(std::move(l)), right(std::move(r)) {}
};

struct CallExpr : Expr {
    std::string callee;
    std::vector<std::shared_ptr<Expr>> args;
    CallExpr(const std::string& c, std::vector<std::shared_ptr<Expr>> a)
        : callee(c), args(std::move(a)) {}
};

struct Statement {
    virtual ~Statement() = default;
};

struct ExprStatement : Statement {
    std::shared_ptr<Expr> expr;
    explicit ExprStatement(std::shared_ptr<Expr> e) : expr(std::move(e)) {}
};

struct PrintStatement : Statement {
    std::shared_ptr<Expr> expr;
    explicit PrintStatement(std::shared_ptr<Expr> e) : expr(std::move(e)) {}
};

struct WhetherStatement : Statement {
    std::shared_ptr<Expr> condition;
    std::vector<std::shared_ptr<Statement>> body;

    WhetherStatement(std::shared_ptr<Expr> cond, std::vector<std::shared_ptr<Statement>> stmts)
        : condition(std::move(cond)), body(std::move(stmts)) {}
};

struct DuringStatement : Statement {
    std::shared_ptr<Expr> condition;
    std::vector<std::shared_ptr<Statement>> body;

    DuringStatement(std::shared_ptr<Expr> cond, std::vector<std::shared_ptr<Statement>> stmts)
        : condition(std::move(cond)), body(std::move(stmts)) {}
};


}
