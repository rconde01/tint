struct tint_symbol {
  float4 value : SV_Position;
};

void tan_244e2a() {
  float4 res = tan(float4(0.0f, 0.0f, 0.0f, 0.0f));
}

tint_symbol vertex_main() {
  tan_244e2a();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  tan_244e2a();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  tan_244e2a();
  return;
}
