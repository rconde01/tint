[[group(1), binding(0)]] var arg_0 : texture_storage_2d<r32float, read>;

fn textureLoad_c07013() {
  var res : vec4<f32> = textureLoad(arg_0, vec2<i32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureLoad_c07013();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureLoad_c07013();
}

[[stage(compute)]]
fn compute_main() {
  textureLoad_c07013();
}