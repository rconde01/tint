#include "debug_transform.h"

#include <string>
#include <utility>

#include "src/tint/ast/attribute.h"
#include "src/tint/ast/builtin_attribute.h"
#include "src/tint/ast/function.h"
#include "src/tint/ast/module.h"
#include "src/tint/ast/struct.h"
#include "src/tint/builtin/builtin_value.h"
#include "src/tint/program_builder.h"
#include "src/tint/sem/function.h"
#include "src/tint/sem/statement.h"
#include "src/tint/sem/struct.h"
#include "src/tint/utils/scoped_assignment.h"
#include "src/tint/utils/vector.h"

TINT_INSTANTIATE_TYPEINFO(tint::transform::DebugTransform);

namespace tint::transform {

struct DebugTransform::State {
  const Program* const src;

  ProgramBuilder b{};

  CloneContext ctx = {&b, src, true};

  const sem::Info& sem = src->Sem();

  const SymbolTable& sym = src->Symbols();
  const ProgramBuilder::TypesBuilder& ty = ctx.dst->ty;

  Transform::ApplyResult Run() {
    utils::Vector<const ast::StructMember*, 2> members;

    members.Push(b.Member("counter", ty.atomic(ty.u32())));
    members.Push(b.Member("data", ty.array(ty.u32())));

    auto dbg_struct =
        ctx.dst->Structure("_DebugBufferContents", std::move(members));

    b.GlobalVar("_dbg_bug", ty.Of(dbg_struct), builtin::AddressSpace::kStorage,
                utils::Vector{b.Binding(AInt(0)), b.Group(AInt(0))});

    ctx.ReplaceAll([&](const ast::Function* fn) -> const ast::Function* {
      // Rebuild the function
      utils::Vector<const ast::Parameter*, 8> params;

      auto name = ctx.Clone(fn->name);
      auto return_type = ctx.Clone(fn->return_type);

      utils::Vector<const ast::Statement*, 8> statements;

      int count{};

      for (auto s : fn->body->statements) {
        statements.Push(ctx.Clone(s));

        if (s->Is<ast::AssignmentStatement>()) {
          auto var = b.Var("wgsl_dbg_" + std::to_string(count++), ty.f32());
          auto var_stmt = b.Decl(var);

          statements.Push(var_stmt);
        }
      }

      auto body_attributes = ctx.Clone(fn->body->attributes);

      auto* body = b.Block(std::move(statements), std::move(body_attributes));
      auto attributes = ctx.Clone(fn->attributes);
      auto return_type_attributes = ctx.Clone(fn->return_type_attributes);

      return b.create<ast::Function>(name, params, return_type, body,
                                     std::move(attributes),
                                     std::move(return_type_attributes));
    });

    ctx.Clone();

    return Program(std::move(b));
  }
};

DebugTransform::DebugTransform() = default;
DebugTransform::~DebugTransform() = default;

Transform::ApplyResult DebugTransform::Apply(const Program* src,
                                             const DataMap&,
                                             DataMap&) const {
  return State{src}.Run();
}

}  // namespace tint::transform