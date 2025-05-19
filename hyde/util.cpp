#include "../include/util.hh"
#include <iostream>
#include <cstdlib>

namespace hyde {

void error(const std::string& message, int line, int column) {
    if (line >= 0 && column >= 0) {
        std::cerr << "[Error] Line " << line << ", Column " << column << ": ";
    } else {
        std::cerr << "[Error] ";
    }

    std::cerr << message << std::endl;
    std::exit(EXIT_FAILURE);
}

}
