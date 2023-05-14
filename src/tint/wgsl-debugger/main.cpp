#include <iostream>

#include "get_syntax_tree.hpp"
#include "get_wgsl.hpp"

auto main() -> int {
  auto src =
      R"(
@vertex fn main_v(@builtin(vertex_index) idx
                             : u32)
               ->@builtin(position) vec4<f32> {
  var pos = array<vec2<f32>, 3>(vec2<f32>(0.0, 0.5), vec2<f32>(-0.5, -0.5),
                                vec2<f32>(0.5, -0.5));
  return vec4<f32>(pos[idx], 0.0, 1.0);
}
@fragment fn main_f(@builtin(position) coord
                    : vec4<f32>, )
    ->@location(0) vec4<f32> {
  var result = vec4<f32>(0.0, coord.x / 300, 1.0, 1.0);  // 0x80/0xff ~= 0.502

  result[0] = result[0];

  return result;
}
)";

  std::cout << get_wgsl(src);

  return 0;
}