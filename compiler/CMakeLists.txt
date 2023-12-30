# minimum cmake version
cmake_minimum_required (VERSION 3.16)

# project name
project(SimpleTest
        VERSION 1.0)


add_definitions("-Wall -g")
add_subdirectory (lib)
add_subdirectory (test)
