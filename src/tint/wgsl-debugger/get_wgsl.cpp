#include <memory>
#include <sstream>
#include <stdexcept>

#include "get_wgsl.hpp"
#include "src/tint/reader/wgsl/parser.h"
#include "src/tint/source.h"
#include "src/tint/writer/wgsl/generator.h"  // nogncheck

auto get_wgsl(std::string const& program_contents) -> std::string {
  auto source_file = std::make_unique<tint::Source::File>(
      "no_file", std::string(program_contents.begin(), program_contents.end()));

  auto program = std::make_unique<tint::Program>(
      tint::reader::wgsl::Parse(source_file.get()));

  tint::writer::wgsl::Options gen_options;

  auto result = tint::writer::wgsl::Generate(program.get(), gen_options);
  if (!result.success) {
    std::ostringstream o;

    o << "Failed to dump AST: " << result.error << std::endl;

    return o.str();
  } else {
    return result.wgsl;
  }
}
