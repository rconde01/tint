// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/transform/emit_vertex_point_size.h"

#include <memory>
#include <utility>

#include "src/ast/assignment_statement.h"
#include "src/ast/block_statement.h"
#include "src/ast/clone_context.h"
#include "src/ast/float_literal.h"
#include "src/ast/identifier_expression.h"
#include "src/ast/scalar_constructor_expression.h"
#include "src/ast/type/f32_type.h"
#include "src/ast/type_manager.h"
#include "src/ast/variable.h"

namespace tint {
namespace transform {
namespace {

const char kPointSizeVar[] = "tint_pointsize";

}  // namespace

EmitVertexPointSize::EmitVertexPointSize() = default;
EmitVertexPointSize::~EmitVertexPointSize() = default;

Transform::Output EmitVertexPointSize::Run(ast::Module* in) {
  Output out;

  if (!in->HasStage(ast::PipelineStage::kVertex)) {
    // If the module doesn't have any vertex stages, then there's nothing to do.
    out.module = in->Clone();
    return out;
  }

  auto* f32 = out.module.create<ast::type::F32>();

  // Declare the pointsize builtin output variable.
  auto* pointsize_var = out.module.create<ast::Variable>(
      Source{},                    // source
      kPointSizeVar,               // name
      ast::StorageClass::kOutput,  // storage_class
      f32,                         // type
      false,                       // is_const
      nullptr,                     // constructor
      ast::VariableDecorationList{
          // decorations
          out.module.create<ast::BuiltinDecoration>(Source{},
                                                    ast::Builtin::kPointSize),
      });
  out.module.AddGlobalVariable(pointsize_var);

  // Build the AST expression & statement for assigning pointsize one.
  auto* one = out.module.create<ast::ScalarConstructorExpression>(
      Source{}, out.module.create<ast::FloatLiteral>(Source{}, f32, 1.0f));
  auto* pointsize_ident = out.module.create<ast::IdentifierExpression>(
      Source{}, out.module.RegisterSymbol(kPointSizeVar), kPointSizeVar);
  auto* pointsize_assign = out.module.create<ast::AssignmentStatement>(
      Source{}, pointsize_ident, one);

  // Add the pointsize assignment statement to the front of all vertex stages.
  ast::CloneContext(&out.module, in)
      .ReplaceAll(
          [&](ast::CloneContext* ctx, ast::Function* func) -> ast::Function* {
            if (func->pipeline_stage() != ast::PipelineStage::kVertex) {
              return nullptr;  // Just clone func
            }
            return CloneWithStatementsAtStart(ctx, func, {pointsize_assign});
          })
      .Clone();

  return out;
}

}  // namespace transform
}  // namespace tint