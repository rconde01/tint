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

#ifndef SRC_SEM_STATEMENT_H_
#define SRC_SEM_STATEMENT_H_

#include "src/sem/node.h"

namespace tint {

// Forward declarations
namespace ast {
class Statement;
}  // namespace ast

namespace sem {

class BlockStatement;

/// Statement holds the semantic information for a statement.
class Statement : public Castable<Statement, Node> {
 public:
  /// Constructor
  /// @param declaration the AST node for this statement
  /// @param parent the owning statement
  Statement(const ast::Statement* declaration, const Statement* parent);

  /// @return the AST node for this statement
  const ast::Statement* Declaration() const { return declaration_; }

  /// @return the statement that encloses this statement
  const Statement* Parent() const { return parent_; }

  /// @return the closest enclosing block for this statement
  const BlockStatement* Block() const;

 private:
  ast::Statement const* const declaration_;
  Statement const* const parent_;
};

}  // namespace sem
}  // namespace tint

#endif  // SRC_SEM_STATEMENT_H_
