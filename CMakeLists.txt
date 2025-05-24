add_executable(hyde
    hydesource/main.cpp
    hydesource/lexer.cpp
    hydesource/parse.cpp
    hydesource/inter.cpp
    hydesource/util.cpp
)

target_include_directories(hyde PRIVATE include)
