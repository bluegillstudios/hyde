add_executable(hyde
    hyde/main.cpp
    hyde/lexer.cpp
    hyde/parse.cpp
    hyde/inter.cpp
    hyde/util.cpp
)

target_include_directories(hyde PRIVATE include)
