#version 310 es
precision mediump float;

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void f() {
  int a = 1;
  int b = 0;
  int r = (a % b);
  return;
}
void main() {
  f();
}

