add_executable(hyde
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/interpreter.cpp
    src/utils.cpp
)

target_include_directories(hyde PRIVATE include)
