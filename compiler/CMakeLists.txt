# minimum cmake version
cmake_minimum_required (VERSION 3.16)

# project name
project(ACC
VERSION 1.0)


add_definitions("-Wall -Werror -g")
add_subdirectory (lib)
link_libraries(lib)
include_directories (PUBLIC lib/inc)

add_executable(acc acc.c)