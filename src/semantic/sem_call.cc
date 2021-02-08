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

#include "src/semantic/call.h"

TINT_INSTANTIATE_CLASS_ID(tint::semantic::Call);
TINT_INSTANTIATE_CLASS_ID(tint::semantic::IntrinsicCall);
TINT_INSTANTIATE_CLASS_ID(tint::semantic::TextureIntrinsicCall);

namespace tint {
namespace semantic {

Call::Call(type::Type* return_type) : Base(return_type) {}

Call::~Call() = default;

IntrinsicCall::IntrinsicCall(type::Type* return_type, IntrinsicType intrinsic)
    : Base(return_type), intrinsic_(intrinsic) {}

IntrinsicCall::~IntrinsicCall() = default;

TextureIntrinsicCall::TextureIntrinsicCall(type::Type* return_type,
                                           IntrinsicType intrinsic,
                                           const Parameters& params)
    : Base(return_type, intrinsic), params_(params) {}

TextureIntrinsicCall::~TextureIntrinsicCall() = default;

TextureIntrinsicCall::Parameters::Index::Index() = default;
TextureIntrinsicCall::Parameters::Index::Index(const Index&) = default;

}  // namespace semantic
}  // namespace tint