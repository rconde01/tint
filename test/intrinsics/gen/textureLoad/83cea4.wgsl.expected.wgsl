[[group(1), binding(0)]] var arg_0 : texture_storage_1d<rgba16uint, read>;

fn textureLoad_83cea4() {
  var res : vec4<u32> = textureLoad(arg_0, 1);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureLoad_83cea4();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureLoad_83cea4();
}

[[stage(compute)]]
fn compute_main() {
  textureLoad_83cea4();
}