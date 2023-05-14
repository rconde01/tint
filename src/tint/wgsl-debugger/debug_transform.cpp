#include "debug_transform.h"

#include <cassert>
#include <string>
#include <utility>

#include "src/tint/ast/attribute.h"
#include "src/tint/ast/builtin_attribute.h"
#include "src/tint/ast/function.h"
#include "src/tint/ast/module.h"
#include "src/tint/ast/stage_attribute.h"
#include "src/tint/ast/struct.h"
#include "src/tint/builtin/builtin_value.h"
#include "src/tint/program_builder.h"
#include "src/tint/sem/function.h"
#include "src/tint/sem/statement.h"
#include "src/tint/sem/struct.h"
#include "src/tint/type/reference.h"
#include "src/tint/type/vector.h"
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
    auto const buf_name = "_wgsl_dbg_buf";
    auto const buf_fragment_num_name = "_wgsl_dbg_fragment_num";
    auto const buf_fragment_offset_name = "_wgsl_dbg_fragment_offset";
    auto const buf_fragment_stride_name = "_wgsl_dbg_fragment_stride";

    auto get_expression_type = [&](ast::Expression const* exp) {
      auto exp_sem = sem.GetVal(exp);
      auto exp_type = exp_sem->Type();

      if (exp_type->Is<tint::type::Reference>()) {
        auto ref = exp_type->As<tint::type::Reference>();
        auto store_type = ref->StoreType();

        using vec_type = tint::type::Vector;

        if (store_type->Is<vec_type>()) {
          auto vec = store_type->As<vec_type>();
          auto element_type = vec->type();

          if (element_type->Is<tint::type::F32>()) {
            switch (vec->Width()) {
              case 2:
                return ExpressionType::vec2_f32;
              case 3:
                return ExpressionType::vec3_f32;
              case 4:
                return ExpressionType::vec4_f32;
              default:
                assert(false);
            }
          } else if (element_type->Is<tint::type::I32>()) {
            switch (vec->Width()) {
              case 2:
                return ExpressionType::vec2_i32;
              case 3:
                return ExpressionType::vec3_i32;
              case 4:
                return ExpressionType::vec4_i32;
              default:
                assert(false);
            }

          } else if (element_type->Is<tint::type::U32>()) {
            switch (vec->Width()) {
              case 2:
                return ExpressionType::vec2_u32;
              case 3:
                return ExpressionType::vec3_u32;
              case 4:
                return ExpressionType::vec4_u32;
              default:
                assert(false);
            }
          }
        } else {
          if (store_type->Is<tint::type::F32>())
            return ExpressionType::f32;
          else if (store_type->Is<tint::type::I32>())
            return ExpressionType::i32;
          else if (store_type->Is<tint::type::U32>())
            return ExpressionType::u32;
        }
      }

      return ExpressionType::i32;
    };

    InstrumentationData i_data{};

    auto add_debug_capture = [&](auto& statements,
                                 ast::AssignmentStatement const* assign) {
      auto capture_type = get_expression_type(assign->lhs);

      // buf.data[fragment_num * stride + offset++] = bitcast<u32>(result.r);

      auto get_indexer = [&](std::uint32_t index) {
        auto buf_data = b.MemberAccessor(b.Ident(buf_name), b.Ident("data"));
        auto buf_data_indexer = b.Add(b.Mul(b.Ident(buf_fragment_num_name),
                                            b.Ident(buf_fragment_stride_name)),
                                      b.Ident(buf_fragment_offset_name));
        auto buf_indexed = b.IndexAccessor(buf_data, buf_data_indexer);

        return buf_indexed;
      };

      switch (capture_type) {
        case ExpressionType::f32:
          statements.Push(b.Assign(
              get_indexer(0),
              b.Bitcast(ty.u32(), ctx.CloneWithoutTransform(assign->lhs))));
          statements.Push(b.Increment(b.Ident(buf_fragment_offset_name)));
          break;
      }
    };

    auto is_fragment_entry = [](ast::Function const* fn) {
      if (!fn->IsEntryPoint())
        return false;

      for (auto a : fn->attributes) {
        if (a->Is<tint::ast::StageAttribute>()) {
          return a->As<tint::ast::StageAttribute>()->stage ==
                 tint::ast::PipelineStage::kFragment;
        }
      }

      return false;
    };

    utils::Vector<const ast::StructMember*, 2> members;

    members.Push(b.Member("counter", ty.atomic(ty.u32())));
    members.Push(b.Member("data", ty.array(ty.u32())));

    auto dbg_struct =
        ctx.dst->Structure("_DebugBufferContents", std::move(members));

    auto dbg_buf = b.GlobalVar(
        buf_name, ty.Of(dbg_struct), builtin::AddressSpace::kStorage,
        utils::Vector{b.Binding(AInt(0)), b.Group(AInt(0))});

    auto dbg_buf_fragment_stride =
        b.GlobalConst(buf_fragment_stride_name, ty.u32(), b.Expr(tint::u32(0)));

    size_t logPointId = 0;

    // For each function
    // * If function is not entry point, add initial parameter which is
    //   the base capture number.
    // * we may need to clone functions used from both fragment and vertex entry
    // points
    //   since the vertex ones may not capture?

    ctx.ReplaceAll([&](const ast::Function* fn) -> const ast::Function* {
      // Rebuild the function
      utils::Vector<const ast::Parameter*, 8> params;

      auto name = ctx.Clone(fn->name);
      auto return_type = ctx.Clone(fn->return_type);

      utils::Vector<const ast::Statement*, 8> statements;

      if (is_fragment_entry(fn)) {
        // let wgsl_buf_fragment_num = atomicAdd(&buf.counter, 1u) - 1u;
        auto access = b.MemberAccessor(dbg_buf, b.Ident("counter"));
        auto access_ref = b.AddressOf(access);
        auto literal_one = b.Expr(tint::u32(1));
        auto func = b.Call(b.Ident("atomicAdd"),
                           tint::utils::Vector{access_ref, literal_one});
        auto literal_one_2 = b.Expr(tint::u32(1));

        auto sub = b.Sub(func, literal_one_2);

        auto let = b.Let(b.Ident(buf_fragment_num_name), sub);

        auto decl = b.Decl(let);

        statements.Push(decl);
      }

      int count{};

      for (auto s : fn->body->statements) {
        statements.Push(ctx.Clone(s));

        if (s->Is<ast::AssignmentStatement>()) {
          add_debug_capture(statements, s->As<ast::AssignmentStatement>());
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