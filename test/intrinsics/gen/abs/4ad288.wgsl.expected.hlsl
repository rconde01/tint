struct tint_symbol {
  float4 value : SV_Position;
};

void abs_4ad288() {
  int res = abs(1);
}

tint_symbol vertex_main() {
  abs_4ad288();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  abs_4ad288();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  abs_4ad288();
  return;
}
