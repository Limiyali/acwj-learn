cmake_minimum_required (VERSION 3.16)

link_libraries()
project(lib
        VERSION 0.1
        LANGUAGES "C")

aux_source_directory(. SRC)
set(INC inc)
add_library(lib STATIC ${SRC})
target_include_directories (lib PUBLIC ${INC})