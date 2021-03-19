// Copyright 2021 The Tint Authors.
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

#include "src/ast/return_statement.h"
#include "src/resolver/resolver.h"
#include "src/resolver/resolver_test_helper.h"

#include "gmock/gmock.h"

namespace tint {
namespace {

class ResolverFunctionValidationTest : public resolver::TestHelper,
                                       public testing::Test {};

TEST_F(ResolverFunctionValidationTest, FunctionNamesMustBeUnique_fail) {
  // fn func -> i32 { return 2; }
  // fn func -> i32 { return 2; }
  Func("func", ast::VariableList{}, ty.i32(),
       ast::StatementList{
           create<ast::ReturnStatement>(Expr(2)),
       },
       ast::DecorationList{});

  Func(Source{Source::Location{12, 34}}, "func", ast::VariableList{}, ty.i32(),
       ast::StatementList{
           create<ast::ReturnStatement>(Expr(2)),
       },
       ast::DecorationList{});

  EXPECT_FALSE(r()->Resolve());
  EXPECT_EQ(r()->error(),
            "12:34 error v-0016: function names must be unique 'func'");
}

TEST_F(ResolverFunctionValidationTest, FunctionEndWithoutReturnStatement_Fail) {
  // fn func -> int { var a:i32 = 2; }

  auto* var = Var("a", ty.i32(), ast::StorageClass::kNone, Expr(2));

  Func(Source{Source::Location{12, 34}}, "func", ast::VariableList{}, ty.i32(),
       ast::StatementList{
           create<ast::VariableDeclStatement>(var),
       },
       ast::DecorationList{});

  EXPECT_FALSE(r()->Resolve());
  EXPECT_EQ(
      r()->error(),
      "12:34 error v-0002: non-void function must end with a return statement");
}

TEST_F(ResolverFunctionValidationTest,
       FunctionEndWithoutReturnStatementEmptyBody_Fail) {
  // fn func -> int {}

  Func(Source{Source::Location{12, 34}}, "func", ast::VariableList{}, ty.i32(),
       ast::StatementList{}, ast::DecorationList{});

  EXPECT_FALSE(r()->Resolve());
  EXPECT_EQ(
      r()->error(),
      "12:34 error v-0002: non-void function must end with a return statement");
}

}  // namespace
}  // namespace tint
