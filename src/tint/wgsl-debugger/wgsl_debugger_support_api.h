#pragma once

#include <span>

using Handle = uint32_t;

enum class DepthLayer { minimum, maximum, index };

auto load_shader(std::string const& shader) -> Handle;
auto release_shader(Handle handle) -> void;
auto get_instrumented_shader(Handle handle) -> std::string;
auto get_debug_buffer_size(Handle handle) -> uint32_t;
auto load_debug_buffer(std::span<std::byte, std::dynamic_extent> debug_buffer)
    -> void;
auto get_capture_count(Handle handle) -> uint32_t;
auto get_capture_source_line(Handle handle, uint32_t capture index) -> uint32_t;
auto set_capture_index(Handle handle, uint32_t index) -> void;
auto get_num_fragment_layers(uint32_t x, uint32_t y) -> uint32_t;
auto set_fragment(uint32_t x, uint32_t y, DepthLayer layer) -> void;
