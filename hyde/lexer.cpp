#include "../include/lexer.hh"
#include <cctype>

namespace hyde {

Lexer::Lexer(const std::string& source) : source(source) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (pos < source.size()) {
        skipWhitespace();
        char current = peek();

        if (std::isalpha(current) || current == '_') {
            tokens.push_back(makeIdentifierOrKeyword());
        } else if (std::isdigit(current)) {
            tokens.push_back(makeNumber());
        } else if (current == '"') {
            tokens.push_back(makeString());
        } else {
            std::string val(1, advance());
            tokens.emplace_back(TokenType::Symbol, val, line, column);
        }
    }

    tokens.emplace_back(TokenType::Eof, "", line, column);
    return tokens;
}

char Lexer::peek() const {
    return pos < source.size() ? source[pos] : '\0';
}

char Lexer::advance() {
    char c = source[pos++];
    column++;
    if (c == '\n') {
        line++;
        column = 1;
    }
    return c;
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) advance();
}

Token Lexer::makeIdentifierOrKeyword() {
    int start = pos;
    while (std::isalnum(peek()) || peek() == '_') advance();

    std::string value = source.substr(start, pos - start);
    TokenType type = (value == "fn" || value == "let" || value == "print")
                     ? TokenType::Keyword
                     : TokenType::Identifier;

    return Token(type, value, line, column);
}

Token Lexer::makeNumber() {
    int start = pos;
    while (std::isdigit(peek())) advance();

    if (peek() == '.') {
        advance();
        while (std::isdigit(peek())) advance();
    }

    std::string value = source.substr(start, pos - start);
    return Token(TokenType::Number, value, line, column);
}

Token Lexer::makeString() {
    advance();  // Skip opening quote
    int start = pos;

    while (peek() != '"' && pos < source.size()) advance();
    std::string value = source.substr(start, pos - start);
    advance();  // Skip closing quote

    return Token(TokenType::String, value, line, column);
}

}
