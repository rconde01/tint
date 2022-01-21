// Copyright 2022 The Tint Authors.
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

#include <string>

#include "src/benchmark/benchmark.h"

namespace tint::writer::hlsl {
namespace {

void GenerateHLSL(::benchmark::State& state, std::string input_name) {
  auto res = benchmark::LoadProgram(input_name);
  if (auto err = std::get_if<benchmark::Error>(&res)) {
    state.SkipWithError(err->msg.c_str());
    return;
  }
  auto& program = std::get<benchmark::ProgramAndFile>(res).program;
  for (auto _ : state) {
    auto res = Generate(&program, {});
    if (!res.error.empty()) {
      state.SkipWithError(res.error.c_str());
    }
  }
}

TINT_BENCHMARK_WGSL_PROGRAMS(GenerateHLSL);

}  // namespace
}  // namespace tint::writer::hlsl