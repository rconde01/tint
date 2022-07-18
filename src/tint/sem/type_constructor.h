// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0(the "License");
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

#ifndef SRC_TINT_SEM_TYPE_CONSTRUCTOR_H_
#define SRC_TINT_SEM_TYPE_CONSTRUCTOR_H_

#include "src/tint/sem/call_target.h"

namespace tint::sem {

/// TypeConstructor is the CallTarget for a type constructor.
class TypeConstructor final : public Castable<TypeConstructor, CallTarget> {
  public:
    /// Constructor
    /// @param type the type that's being constructed
    /// @param parameters the type constructor parameters
    /// @param stage the earliest evaluation stage for the expression
    TypeConstructor(const sem::Type* type, const ParameterList& parameters, EvaluationStage stage);

    /// Destructor
    ~TypeConstructor() override;
};

}  // namespace tint::sem

#endif  // SRC_TINT_SEM_TYPE_CONSTRUCTOR_H_
