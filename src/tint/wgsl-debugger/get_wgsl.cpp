#include <memory>
#include <sstream>
#include <stdexcept>

#include "debug_transform.h"
#include "get_wgsl.hpp"
#include "src/tint/clone_context.h"
#include "src/tint/program_builder.h"
#include "src/tint/reader/wgsl/parser.h"
#include "src/tint/source.h"
#include "src/tint/utils/block_allocator.h"
#include "src/tint/writer/syntax_tree/generator.h"
#include "src/tint/writer/wgsl/generator.h"

// from clone_context_test.cc
// struct Allocator {
//     template <typename T, typename... ARGS>
//     T* Create(ARGS&&... args) {
//         return alloc.Create<T>(this, std::forward<ARGS>(args)...);
//     }

//   private:
//     tint::utils::BlockAllocator<tint::Cloneable> alloc;
// };

auto get_wgsl(std::string const& program_contents) -> std::string {
  std::ostringstream o;

  auto source_file = std::make_unique<tint::Source::File>(
      "no_file", std::string(program_contents.begin(), program_contents.end()));

  auto program = std::make_unique<tint::Program>(
      tint::reader::wgsl::Parse(source_file.get()));

  if (!program->IsValid()) {
    return "Error parsing original program.";
  }

  // auto ast_result = tint::writer::syntax_tree::Generate(
  //     program.get(), tint::writer::syntax_tree::Options{});

  // o << ast_result.ast;

  tint::transform::DebugTransform tranform;

  tint::transform::DataMap output;

  auto trans_result = tranform.Apply(program.get(), {}, output);

  tint::writer::wgsl::Options gen_options;

  auto result = tint::writer::wgsl::Generate(&*trans_result, gen_options);
  if (!result.success) {
    o << "Failed to dump AST: " << result.error << std::endl;

  } else {
    o << result.wgsl;
  }

  return o.str();
}
