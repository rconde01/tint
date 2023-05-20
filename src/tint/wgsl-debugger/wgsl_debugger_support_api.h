#pragma once

#include <array>
#include <span>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

using Handle = uint32_t;

enum class DepthLayer { minimum, maximum, index };

using VariableValue = std::variant<bool,
                                   std::array<bool, 2>,
                                   std::array<bool, 3>,
                                   std::array<bool, 4>,
                                   int32_t,
                                   std::array<int32_t, 2>,
                                   std::array<int32_t, 3>,
                                   std::array<int32_t, 4>,
                                   uint32_t,
                                   std::array<uint32_t, 2>,
                                   std::array<uint32_t, 3>,
                                   std::array<uint32_t, 4>,
                                   float,
                                   std::array<float, 2>,
                                   std::array<float, 3>,
                                   std::array<float, 4>>;

struct VariableInfo {
  std::string name;
  std::string type;
  VariableValue value;
};

auto load_shader(std::string const& shader) -> Handle;
auto release_shader(Handle handle) -> void;
auto get_instrumented_shader(Handle handle) -> std::string;
auto get_debug_buffer_size(Handle handle) -> uint32_t;
auto load_debug_buffer(std::span<std::byte, std::dynamic_extent> debug_buffer)
    -> void;
auto get_num_fragment_layers(uint32_t x, uint32_t y) -> uint32_t;
auto set_fragment(uint32_t x,
                  uint32_t y,
                  DepthLayer layer,
                  uint32_t layer_index) -> void;
auto set_capture_index(Handle handle, uint32_t index) -> void;
auto get_capture_count(Handle handle) -> uint32_t;
auto get_capture_type(Handle handle) -> std::string;
auto get_capture_callstack(Handle handle) -> std::vector<std::string>;
auto get_capture_source_line(Handle handle) -> uint32_t;
auto get_variables(Handle handle) -> std::vector<VariableInfo>;
