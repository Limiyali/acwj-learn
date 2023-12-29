aux_source_directory(. SRC)

link_libraries(lib)

foreach (file ${SRC})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    # 源文件名称中包含[.c]的文件
    if (${file} MATCHES .c)
        add_executable(${exe} ${file})
        message(------------ 添加文件: ${file})
        continue()
    endif ()
    message(************ 跳过文件: ${file})
endforeach ()

include_directories (PUBLIC ../lib/inc)
