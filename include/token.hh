#pragma once
#include <string>

namespace hyde {

enum class TokenType {
    Identifier,
    Number,
    String,
    Keyword,
    Symbol,
    Operator,
    Eof,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;

    Token(TokenType t, const std::string& v, int l, int c)
        : type(t), value(v), line(l), column(c) {}
};

}
