#version 310 es
precision mediump float;

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void unused_entry_point() {
  return;
}
void main() {
  unused_entry_point();
}



const ivec4 v = ivec4(0, 1, 2, 3);