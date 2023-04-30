add_executable(wgsl-debugger embind.cpp get_syntax_tree.cpp)

tint_default_compile_options(wgsl-debugger)

target_link_libraries(wgsl-debugger
    PRIVATE libtint
)

target_link_options(wgsl-debugger
    PRIVATE -lembind
    PRIVATE -fwasm-exceptions
)

target_compile_options(wgsl-debugger
    PRIVATE -fwasm-exceptions
)

configure_file(index.html "${CMAKE_BINARY_DIR}/wgsl-debugger.html" COPYONLY)