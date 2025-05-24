#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../include/lexer.hh"
#include "../include/parser.hh"
#include "../include/inter.hh"
#include "../include/util.hh"
#include "../include/token.hh"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: hyde <file.hy>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    try {
        hyde::Lexer lexer(source);
        auto tokens = lexer.tokenize();

        hyde::Parser parser(tokens);
        auto statements = parser.parse();

        hyde::Interpreter interpreter;
        interpreter.interpret(statements);
    } catch (const std::exception& e) {
        std::cerr << "[Fatal Error] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
