#pragma once
#include <vector>
#include <string>
#include "token.hh"

namespace hyde {

class Lexer {
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos = 0;
    int line = 1;
    int column = 1;

    char peek() const;
    char advance();
    void skipWhitespace();
    Token makeIdentifierOrKeyword();
    Token makeNumber();
    Token makeString();
};

}
