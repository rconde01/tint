SKIP: FAILED

#version 310 es
precision mediump float;

struct buf0 {
  float one;
};

layout (binding = 0) uniform buf0_1 {
  float one;
} x_6;
vec4 x_GLF_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

void main_1() {
  float f = 0.0f;
  float x_28 = x_6.one;
  f = (4.0f / (2.0f * x_28));
  if (((f > 1.899999976f) & (f < 2.099999905f))) {
    x_GLF_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  } else {
    x_GLF_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
  }
  return;
}

struct main_out {
  vec4 x_GLF_color_1;
};
struct tint_symbol_1 {
  vec4 x_GLF_color_1;
};

main_out tint_symbol_inner() {
  main_1();
  main_out tint_symbol_2 = main_out(x_GLF_color);
  return tint_symbol_2;
}

tint_symbol_1 tint_symbol() {
  main_out inner_result = tint_symbol_inner();
  tint_symbol_1 wrapper_result = tint_symbol_1(vec4(0.0f, 0.0f, 0.0f, 0.0f));
  wrapper_result.x_GLF_color_1 = inner_result.x_GLF_color_1;
  return wrapper_result;
}
out vec4 x_GLF_color_1;
void main() {
  tint_symbol_1 outputs;
  outputs = tint_symbol();
  x_GLF_color_1 = outputs.x_GLF_color_1;
}


Error parsing GLSL shader:
ERROR: 0:17: '&' :  wrong operand types: no operation '&' exists that takes a left-hand operand of type ' temp bool' and a right operand of type ' temp bool' (or there is no acceptable conversion)
ERROR: 0:17: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.


