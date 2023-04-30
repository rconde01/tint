#include <memory>
#include <sstream>
#include <stdexcept>

#include "get_syntax_tree.hpp"
#include "src/tint/reader/wgsl/parser.h"
#include "src/tint/source.h"
#include "src/tint/writer/syntax_tree/generator.h"  // nogncheck

auto get_syntax_tree(std::string const& program_contents) -> std::string {
  auto source_file = std::make_unique<tint::Source::File>(
      "no_file", std::string(program_contents.begin(), program_contents.end()));

  auto program = std::make_unique<tint::Program>(
      tint::reader::wgsl::Parse(source_file.get()));

  tint::writer::syntax_tree::Options gen_options;

  auto result = tint::writer::syntax_tree::Generate(program.get(), gen_options);
  if (!result.success) {
    std::ostringstream o;

    o << "Failed to dump AST: " << result.error << std::endl;

    return o.str();
  } else {
    return result.ast;
  }
}
