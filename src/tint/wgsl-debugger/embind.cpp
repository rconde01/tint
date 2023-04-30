#include <emscripten/bind.h>

using namespace emscripten;

#include "get_syntax_tree.hpp"

EMSCRIPTEN_BINDINGS(my_tint_module) {
  function("get_syntax_tree", &get_syntax_tree);
}
