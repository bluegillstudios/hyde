#pragma once
#include <string>

namespace hyde {

[[noreturn]] void error(const std::string& message, int line = -1, int column = -1);

}
