struct tint_symbol {
  float4 value : SV_Position;
};

void fwidth_df38ef() {
  float res = fwidth(1.0f);
}

tint_symbol vertex_main() {
  fwidth_df38ef();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  fwidth_df38ef();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  fwidth_df38ef();
  return;
}
