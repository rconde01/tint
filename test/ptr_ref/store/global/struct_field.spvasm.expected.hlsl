struct S {
  int i;
};

static S V;

void main_1() {
  V.i = 5;
  return;
}

[numthreads(1, 1, 1)]
void main() {
  main_1();
  return;
}
