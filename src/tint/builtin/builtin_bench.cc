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
//   src/tint/builtin/builtin_bench.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/builtin/builtin.h"

#include <array>

#include "benchmark/benchmark.h"

namespace tint::builtin {
namespace {

void BuiltinParser(::benchmark::State& state) {
    const char* kStrings[] = {
        "__acked_veccc",
        "_pac3ed_v3",
        "__packeV_vec3",
        "__packed_vec3",
        "__pa1ked_vec3",
        "_qqJcked_vec3",
        "__pack77d_vllc3",
        "arqHapp",
        "vy",
        "Grby",
        "array",
        "arviay",
        "ar8WWy",
        "Mxxra",
        "atXggi",
        "Xoic",
        "ato3ic",
        "atomic",
        "aEomic",
        "toTTiPP",
        "ddtoxxi",
        "44ool",
        "VVSSol",
        "RoRl",
        "bool",
        "oFl",
        "boo",
        "ORVHl",
        "y1",
        "l77rrn6",
        "4016",
        "f16",
        "5",
        "u16",
        "f",
        "f3kk",
        "fi",
        "f3XX",
        "f32",
        "55399II",
        "frSSHHa",
        "U",
        "jV3",
        "",
        "GG",
        "i32",
        "2",
        "",
        "jj",
        "a2xrf",
        "mat2j2",
        "m82wNN2",
        "mat2x2",
        "mt2x2",
        "rrat2x2",
        "mGt2x2",
        "mat2x2FF",
        "at2f",
        "marrx2f",
        "mat2x2f",
        "t2x2f",
        "Da2xJJf",
        "ma82",
        "m11k2",
        "matx2h",
        "maJx2h",
        "mat2x2h",
        "mat2c2h",
        "mat2x2O",
        "KK_atvvtt2h",
        "5txxx8",
        "a__xqq",
        "maqq2x",
        "mat2x3",
        "ma32x66",
        "mttQQo2x3",
        "mat66x",
        "mtOxzz66",
        "mat2yy3f",
        "ZaHH3Z",
        "mat2x3f",
        "4WWt2q3f",
        "mOO2x3f",
        "oatY3f",
        "matx",
        "ma2xFh",
        "at2x3w",
        "mat2x3h",
        "fGtxKh",
        "matqKx3h",
        "matmmxFh",
        "at2x4",
        "matxq",
        "mb2bb4",
        "mat2x4",
        "it2x4",
        "mOO2xq",
        "mat2Tvv4",
        "maFF2x4f",
        "Pa00xQf",
        "mPt2x4f",
        "mat2x4f",
        "ma772xss",
        "RRCbb2x4f",
        "mXXt2x4f",
        "qaCC2xOOh",
        "ma2s4L",
        "mXt2x4h",
        "mat2x4h",
        "mat24h",
        "qa2O4",
        "mat2x22h",
        "mzzyt3x",
        "atiVP2",
        "mt3Cnn",
        "mat3x2",
        "AtqqHH2",
        "at3x2",
        "mafKK",
        "ltgg2f",
        "mat3xf",
        "NTTtcx4f",
        "mat3x2f",
        "ma7ppl2f",
        "mNNt3xg",
        "uub3XX2f",
        "matx2h",
        "Qt882h",
        "mt9q2h",
        "mat3x2h",
        "m11t3x2h",
        "22at3iih",
        "at3x277",
        "NNa323",
        "VVat3x3",
        "ma11F3w3",
        "mat3x3",
        "matww3",
        "mat3D3",
        "maKx3",
        "mat31PPhf",
        "mat33f",
        "mYYt3x3f",
        "mat3x3f",
        "mttHH3kk",
        "mat3rr3f",
        "WWas3x3f",
        "Yt3x3h",
        "mt3qfh",
        "mav223xuh",
        "mat3x3h",
        "t3x3h",
        "YYat3h",
        "may3x3EYY",
        "Moatd4",
        "mt3xMM",
        "m55t3x4",
        "mat3x4",
        "maN4",
        "ma33x4",
        "mt3x3",
        "mm66Issf",
        "mat3x1f",
        "Xt3x4",
        "mat3x4f",
        "LatIx4f",
        "at3ff",
        "mYtURD4",
        "mah3x4h",
        "uuIqt3x",
        "maH3x4h",
        "mat3x4h",
        "at3QQvv",
        "at66eh",
        "ma7O4h",
        "m0t55DD2",
        "IIaH4x2",
        "mat4x",
        "mat4x2",
        "mt4r2",
        "mat4xl",
        "mGttx2",
        "mat4y2",
        "mt4x2f",
        "IIaBB4x2f",
        "mat4x2f",
        "TTat4x833",
        "ddUUnntYYx2f",
        "m5CCxxdZ",
        "matkkq2h",
        "005itpxh",
        "maIInnx2h",
        "mat4x2h",
        "Ka4Wcc",
        "m42KK",
        "mat66x2h",
        "mKKtPx",
        "maxx43",
        "matqx3",
        "mat4x3",
        "rMtyyxSS",
        "uat4",
        "tx3",
        "ma5F4x3f",
        "rra444z3f",
        "matWW",
        "mat4x3f",
        "CatZJXx3f",
        "maPPx3f",
        "mat4c3f",
        "matPPll6h",
        "mat993yy",
        "mat4JKKh",
        "mat4x3h",
        "mat4_h",
        "ayK3h",
        "mzt4V3k",
        "qaSKx4",
        "mat44",
        "ma4xVV",
        "mat4x4",
        "mAAt4xI",
        "jb44",
        "t4YYx",
        "mao4x4",
        "mtx114f",
        "mtmxccf",
        "mat4x4f",
        "aJJ4x4f",
        "fCCDD4x4U",
        "mgt4x4f",
        "CCx4h",
        "mat4x66",
        "maN4M4h",
        "mat4x4h",
        "mattth",
        "maKWxh",
        "mateezx4h",
        "",
        "w9",
        "4tnn",
        "ptr",
        "tll",
        "4to",
        "wEgg",
        "gamler",
        "spleS",
        "aampl",
        "sampler",
        "TamplZRRr",
        "sa8TplOr",
        "m0ampler",
        "sampler_Bmomparison",
        "Mamper_ppomarison",
        "samper_compOOrison",
        "sampler_comparison",
        "sampler_compGrGGon",
        "sHHm11ler_comparison",
        "sa6ler_FFeemparison",
        "texure_1",
        "tKiilure_1d",
        "exture_1d",
        "texture_1d",
        "99etvIIre_1d",
        "texture_d",
        "texture_hd",
        "llxzzure_PPd",
        "exue2d",
        "tffqqtre_2d",
        "texture_2d",
        "texturJdd_d",
        "trXXtu_2zz",
        "textu2e2d",
        "tNyyture_2d_array",
        "txture_2d_rOOa",
        "textureErduaZPay",
        "texture_2d_array",
        "exl22re_2dd_areeay",
        "mextureVV_ar9ay",
        "teIItu1_2d_array",
        "tebture_3d",
        "ie7ure3d",
        "teotiire_3d",
        "texture_3d",
        "extre_35",
        "textre_iS",
        "t22xtur_3",
        "teC711recuGe",
        "texture8cffbe",
        "textue_cue",
        "texture_cube",
        "texture_SSJJbe",
        "textrecu9e",
        "TTeJJbture_cube",
        "t66ture_cube_aray",
        "textur66_cubu_arra",
        "textureWubeyarray",
        "texture_cube_array",
        "texture_cube_ara",
        "texture_ube_array",
        "rexture_cube_array",
        "tex2ure_depth_2B",
        "texture_dpBBh_2d",
        "texture_dpth_RRd",
        "texture_depth_2d",
        "tLL0Vure_deth_2d",
        "tetKKredOOpth_2d",
        "textgwre_dpth_2d",
        "textue_depthLh2d_arpay",
        "texture_depEh2diiKrray",
        "texture_dept_2d_array",
        "texture_depth_2d_array",
        "t88xtuUUe_deph_2d_rray",
        "texrruvve_depth_2d_array",
        "texture_depmm_2d_wray",
        "tjture_d44pth_cube",
        "texture_depth_cXbe",
        "t8xture_depth_cube",
        "texture_depth_cube",
        "textur_devvth_cubEE",
        "tzxturi99epth_cube",
        "teQQtuJJGe_nepth_cuAe",
        "texture_depth_cusse_array",
        "texture_Pepth_cKbe_array",
        "texture_dppp_cube_attray",
        "texture_depth_cube_array",
        "exture_deth_cube_array",
        "texture_depth_MMube_array",
        "tJJxture_depth_cube_a0ray",
        "textu8_dpth_mulisampled_2V",
        "texture_dhhpth_mKltisggmpled_2d",
        "texture_depth_multisampledf2d",
        "texture_depth_multisampled_2d",
        "te77ture_depth_multisamQled_2d",
        "teture_depthYYmultisampled_2d",
        "texture_deptk_multiampled_Sd",
        "txturn_ext2rnal",
        "txture_FFternal",
        "texUPPIre_GGxuernal",
        "texture_external",
        "taxtuvEE_externl",
        "textureexBddernDDl",
        "tEEMtur_e55tccrnal",
        "texturemuKKtisample_d",
        "texture_multisRmpled_2d",
        "texturemulDisampl9d_2d",
        "texture_multisampled_2d",
        "teture_multisampled_2d",
        "textuIa_multisampld_2d",
        "texture_multisamp77ed_2d",
        "texIure_storage_1d",
        "texture_storagedd",
        "texture_storae_1d",
        "texture_storage_1d",
        "texture_strate_d",
        "texture33stoXXcge_1d",
        "texturestorage_1E",
        "textuXXestorage_2d",
        "texture_stoBaxxe_2d",
        "texte_storWge_2G",
        "texture_storage_2d",
        "texture_s66orage_2d",
        "textvTr_so0age_2d",
        "textureorgek2d",
        "textppre_stoae_2d_array",
        "textre_stora11e_d_array",
        "textureystorBEgeJ2d_array",
        "texture_storage_2d_array",
        "texture_mtorage_2dxIqrray",
        "teture_storageF2d_array",
        "textur_Ytorage_2d_array",
        "heDture_sHHorage_3d",
        "texturstorage23H",
        "teture_strage_3d",
        "texture_storage_3d",
        "texture_storage_d",
        "texturestorage_3d",
        "ddexture_storage_3d",
        "uPO",
        "ba",
        "u02",
        "u32",
        "h32",
        "gYY",
        "O32",
        "eh",
        "ppfe2",
        "vev",
        "vec2",
        "vzz2",
        "vc2",
        "OOii",
        "vGc2f",
        "22ecTTf",
        "dlc2f",
        "vec2f",
        "vecbf",
        "ec2BB",
        "IIScXPP",
        "jjec2h",
        "cc_c2h",
        "zz6xx2h",
        "vec2h",
        "c2",
        "4xx2N",
        "p0AAeh",
        "vey2",
        "vbWW0i",
        "meMMtti",
        "vec2i",
        "di",
        "vvc_",
        "VEEc2i",
        "vec24",
        "VVeX2u",
        "veVou",
        "vec2u",
        "ve2u",
        "ecKKt",
        "eG",
        "ea3",
        "OOc",
        "G",
        "vec3",
        "ve53",
        "9fjec3",
        "vvXcRY",
        "ccf",
        "v8XX5",
        "ec3",
        "vec3f",
        "ppc3cc",
        "vecvf",
        "eEE3SS",
        "vec",
        "eh",
        "ec3ww",
        "vec3h",
        "vecd99h",
        "ve99P",
        "KKec3",
        "ooMcDD",
        "vei",
        "vqi",
        "vec3i",
        "veL30",
        "vncvv66",
        "vrrn3",
        "vxxce",
        "NCCOc3u",
        "vc3u",
        "vec3u",
        "aec4u",
        "NNc3NN",
        "ve3u",
        "vc",
        "vAYS4",
        "vec0",
        "vec4",
        "vecaa",
        "mmcq",
        "vc4",
        "vE4U",
        "veKD4",
        "v0t4__",
        "vec4f",
        "cpA",
        "ec4f",
        "vBBc4f",
        "vbnn99",
        "EEcAAh",
        "v5c66h",
        "vec4h",
        "vHc4h",
        "vecxh",
        "vzyn40",
        "ve4i",
        "kH4i",
        "veci",
        "vec4i",
        "oo4rr",
        "JJc4",
        "vcCC0",
        "xAA99F",
        "veccu",
        "vec4S",
        "vec4u",
        "vocBB",
        "ec4u",
        "veemm",
    };
    for (auto _ : state) {
        for (auto* str : kStrings) {
            auto result = ParseBuiltin(str);
            benchmark::DoNotOptimize(result);
        }
    }
}

BENCHMARK(BuiltinParser);

}  // namespace
}  // namespace tint::builtin
