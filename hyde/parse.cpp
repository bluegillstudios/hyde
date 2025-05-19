#include "../include/parser.hh"
#include "../include/util.hh"
#include <stdexcept>

namespace hyde {

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::vector<std::shared_ptr<Statement>> Parser::parse() {
    std::vector<std::shared_ptr<Statement>> statements;
    while (!isAtEnd()) {
        statements.push_back(statement());
    }
    return statements;
}

std::shared_ptr<Statement> Parser::statement() {
    if (match(TokenType::Keyword) && peek().value == "print") {
        advance(); // consume 'print'
        return printStatement();
    }
    return exprStatement();
}

std::shared_ptr<Statement> Parser::printStatement() {
    auto expr = expression();
    return std::make_shared<PrintStatement>(expr);
}

std::shared_ptr<Statement> Parser::exprStatement() {
    auto expr = expression();
    return std::make_shared<ExprStatement>(expr);
}

std::shared_ptr<Statement> Parser::whetherStatement() {
    if (match(TokenType::Keyword) && peek().value == "whether") {
        advance(); 
        auto condition = expression();
        if (!(match(TokenType::Operator) && peek().value == "{")) {
            throw std::runtime_error("Expected '{' after whether condition.");
        }
        advance(); 
        std::vector<std::shared_ptr<Statement>> body;

        while (!(match(TokenType::Operator) && peek().value == "}")) {
            body.push_back(statement());
        }
        advance(); 

        return std::make_shared<WhetherStatement>(condition, body);
    }
    throw std::runtime_error("Expected 'whether' statement.");
}

std::shared_ptr<Statement> Parser::duringStatement() {
    if (match(TokenType::Keyword) && peek().value == "during") {
        advance(); 
        auto condition = expression();
        if (!(match(TokenType::Operator) && peek().value == "{")) {
            throw std::runtime_error("Expected '{' after during condition.");
        }
        advance(); 
        std::vector<std::shared_ptr<Statement>> body;

        while (!(match(TokenType::Operator) && peek().value == "}")) {
            body.push_back(statement());
        }
        advance(); 

        return std::make_shared<DuringStatement>(condition, body);
    }
    throw std::runtime_error("Expected 'during' statement.");
}

std::shared_ptr<Expr> Parser::expression() {
    return binaryOp(0);
}

std::shared_ptr<Expr> Parser::binaryOp(int precedence) {
    auto left = primary();

    
    if (peek().type == TokenType::Operator && peek().value == "=") {
        advance(); 
        auto value = expression();
        if (auto varExpr = std::dynamic_pointer_cast<VariableExpr>(left)) {
            return std::make_shared<AssignExpr>(varExpr->name, value);
        } else {
            throw std::runtime_error("Invalid assignment target.");
        }
    }

    while (!isAtEnd() && peek().type == TokenType::Operator) {
        int prec = getPrecedence(peek());
        if (prec < precedence) break;

        std::string op = advance().value;
        auto right = binaryOp(prec + 1);
        left = std::make_shared<BinaryExpr>(op, left, right);
    }

    return left;
}

std::shared_ptr<Expr> Parser::primary() {
    const Token& tok = advance();

    switch (tok.type) {
        case TokenType::Number:
            return std::make_shared<NumberExpr>(std::stod(tok.value));
        case TokenType::Identifier:
            return std::make_shared<VariableExpr>(tok.value);
        default:
            throw std::runtime_error("Unexpected token: " + tok.value + " at line " + std::to_string(tok.line) + ", column " + std::to_string(tok.column));
    }
}



bool Parser::match(TokenType type) {
    return !isAtEnd() && peek().type == type;
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

const Token& Parser::peek() const {
    return tokens[current];
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::Eof;
}

int Parser::getPrecedence(const Token& token) const {
    if (token.value == "+" || token.value == "-") return 1;
    if (token.value == "*" || token.value == "/") return 2;
    return 0;
}

}
