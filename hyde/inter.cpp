#include "../include/inter.hh"
#include <iostream>
#include <stdexcept>
#include <unordered_map>

namespace hyde {

void Interpreter::interpret(const std::vector<std::shared_ptr<Statement>>& statements) {
    for (const auto& stmt : statements) {
        execute(stmt);
    }
}

void Interpreter::execute(const std::shared_ptr<Statement>& stmt) {
    if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(stmt)) {
        executeExprStatement(exprStmt);
    } else if (auto printStmt = std::dynamic_pointer_cast<PrintStatement>(stmt)) {
        executePrintStatement(printStmt);
    } else {
        throw std::runtime_error("Unknown statement type");
    }
}

void Interpreter::executeExprStatement(const std::shared_ptr<ExprStatement>& stmt) {
    evaluate(stmt->expr); // Ignore result
}

void Interpreter::executePrintStatement(const std::shared_ptr<PrintStatement>& stmt) {
    double value = evaluate(stmt->expr);
    std::cout << value << std::endl;
}

double Interpreter::evaluate(const std::shared_ptr<Expr>& expr) {
    if (auto num = std::dynamic_pointer_cast<NumberExpr>(expr)) {
        return num->value;
    } else if (auto bin = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
        double left = evaluate(bin->left);
        double right = evaluate(bin->right);
        if (bin->op == "+") return left + right;
        if (bin->op == "-") return left - right;
        if (bin->op == "*") return left * right;
        if (bin->op == "/") return left / right;
        throw std::runtime_error("Unknown operator: " + bin->op);
    } else if (auto var = std::dynamic_pointer_cast<VariableExpr>(expr)) {
        if (environment.find(var->name) != environment.end()) {
            return environment[var->name];
        } else {
            throw std::runtime_error("Undefined variable: " + var->name);
        }
    } else if (auto assign = std::dynamic_pointer_cast<AssignExpr>(expr)) {
        double val = evaluate(assign->value);
        environment[assign->name] = val;
        return val;
    } else {
        throw std::runtime_error("Unknown expression type");
    }
}

void Interpreter::execute(const std::shared_ptr<Statement>& stmt) {
    if (auto exprStmt = std::dynamic_pointer_cast<ExprStatement>(stmt)) {
        executeExprStatement(exprStmt);
    } else if (auto printStmt = std::dynamic_pointer_cast<PrintStatement>(stmt)) {
        executePrintStatement(printStmt);
    } else if (auto duringStmt = std::dynamic_pointer_cast<DuringStatement>(stmt)) {
        while (evaluate(duringStmt->condition)) {
            for (const auto& s : duringStmt->body) {
                execute(s);
            }
        }
    } else if (auto whetherStmt = std::dynamic_pointer_cast<WhetherStatement>(stmt)) {
        if (evaluate(whetherStmt->condition)) {
            for (const auto& s : whetherStmt->body) {
                execute(s);
            }
        }
    } else {
        throw std::runtime_error("Unknown statement type");
    }
}

}
