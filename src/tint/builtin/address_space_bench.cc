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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/builtin/address_space_bench.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/builtin/address_space.h"

#include <array>

#include "benchmark/benchmark.h"

namespace tint::builtin {
namespace {

void AddressSpaceParser(::benchmark::State& state) {
    const char* kStrings[] = {
        "ccin",
        "3",
        "_Vin",
        "__in",
        "1_in",
        "_qiJ",
        "_lli77",
        "__qHupp",
        "vt",
        "G_bt",
        "__out",
        "__viut",
        "__8WWt",
        "Mxxou",
        "fuXggton",
        "fuXtou",
        "funct3on",
        "function",
        "funEtion",
        "PPncTTion",
        "xxuncddon",
        "p44ivate",
        "prSSvaVVe",
        "RriR22e",
        "private",
        "pFva9e",
        "priate",
        "VOORRHte",
        "push_constyn",
        "punnh_crr77stallt",
        "pu4h_cons00ant",
        "push_constant",
        "puoo_costan",
        "ushzzcnstant",
        "push_coii11apt",
        "storaXXe",
        "9II5tnnrage",
        "stoaSSrHHYe",
        "storage",
        "stkke",
        "jtogRa",
        "sbrag",
        "unifojm",
        "niform",
        "qform",
        "uniform",
        "uniNNrm",
        "nifrvv",
        "QQiform",
        "workrorf",
        "workjroup",
        "wNNorkrou2",
        "workgroup",
        "workgrop",
        "rrorkgroup",
        "workgroGp",
    };
    for (auto _ : state) {
        for (auto* str : kStrings) {
            auto result = ParseAddressSpace(str);
            benchmark::DoNotOptimize(result);
        }
    }
}

BENCHMARK(AddressSpaceParser);

}  // namespace
}  // namespace tint::builtin
