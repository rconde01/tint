[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rgba16uint, read>;

fn textureNumLayers_57092f() {
  var res : i32 = textureNumLayers(arg_0);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureNumLayers_57092f();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureNumLayers_57092f();
}

[[stage(compute)]]
fn compute_main() {
  textureNumLayers_57092f();
}