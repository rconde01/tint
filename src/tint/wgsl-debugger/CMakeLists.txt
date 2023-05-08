add_executable(wgsl-debugger
    get_syntax_tree.cpp
    get_wgsl.cpp
    debug_transform.cpp
)

if(EMSCRIPTEN)
    target_sources(wgsl-debugger PRIVATE embind.cpp)
else()
    target_sources(wgsl-debugger PRIVATE main.cpp)
endif()


tint_default_compile_options(wgsl-debugger)

target_link_libraries(wgsl-debugger
    PRIVATE libtint
)

if(EMSCRIPTEN)
    target_link_options(wgsl-debugger
        PRIVATE -lembind
        PRIVATE -fwasm-exceptions
    )

    target_compile_options(wgsl-debugger
        PRIVATE -fwasm-exceptions
    )

    configure_file(index.html "${CMAKE_BINARY_DIR}/wgsl-debugger.html" COPYONLY)
endif()