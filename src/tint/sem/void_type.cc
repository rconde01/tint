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

#include "src/tint/sem/void_type.h"

#include "src/tint/program_builder.h"

TINT_INSTANTIATE_TYPEINFO(tint::sem::Void);

namespace tint {
namespace sem {

Void::Void() = default;

Void::Void(Void&&) = default;

Void::~Void() = default;

std::string Void::type_name() const {
  return "__void";
}

std::string Void::FriendlyName(const SymbolTable&) const {
  return "void";
}

}  // namespace sem
}  // namespace tint