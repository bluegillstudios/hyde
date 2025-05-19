#pragma once
#include <memory>
#include "ast.hh"
#include <unordered_map>

namespace hyde {

class Interpreter {
public:
    void interpret(const std::vector<std::shared_ptr<Statement>>& statements);
    std::unordered_map<std::string, double> environment;

private:
    void execute(const std::shared_ptr<Statement>& stmt);
    double evaluate(const std::shared_ptr<Expr>& expr);

    void executeExprStatement(const std::shared_ptr<ExprStatement>& stmt);
    void executePrintStatement(const std::shared_ptr<PrintStatement>& stmt);
};

}
