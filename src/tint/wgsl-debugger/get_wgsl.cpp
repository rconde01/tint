#include <memory>
#include <sstream>
#include <stdexcept>

#include "get_wgsl.hpp"
#include "src/tint/reader/wgsl/parser.h"
#include "src/tint/source.h"
#include "src/tint/writer/wgsl/generator.h"  // nogncheck
#include "src/tint/clone_context.h"
#include "src/tint/program_builder.h"
#include "src/tint/utils/block_allocator.h"

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
  auto source_file = std::make_unique<tint::Source::File>(
      "no_file", std::string(program_contents.begin(), program_contents.end()));

  auto program = std::make_unique<tint::Program>(
      tint::reader::wgsl::Parse(source_file.get()));

  auto builder = tint::ProgramBuilder();

  tint::CloneContext ctx(&builder,program.get());

  auto functions = program->AST().Functions();

  for(auto f : functions){
    if(f->IsEntryPoint()){
        for(auto s : f->body->statements){
            ctx.InsertAfter(
                f->body->statements,
                s,
                builder.Var(
                    "wgsl_dgb_",
                    tint::ast::Type{ builder.Expr(builder.Ident("f32"))}
                )
            );
        }
    }
  }

  ctx.Clone();

  auto new_program = tint::Program(std::move(builder));

  tint::writer::wgsl::Options gen_options;

  auto result = tint::writer::wgsl::Generate(&new_program, gen_options);
  if (!result.success) {
    std::ostringstream o;

    o << "Failed to dump AST: " << result.error << std::endl;

    return o.str();
  } else {
    return result.wgsl;
  }
}
