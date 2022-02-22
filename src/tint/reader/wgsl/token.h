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

#ifndef SRC_TINT_READER_WGSL_TOKEN_H_
#define SRC_TINT_READER_WGSL_TOKEN_H_

#include <string>
#include <string_view>
#include <variant>  // NOLINT: cpplint doesn't recognise this

#include "src/tint/source.h"

namespace tint {
namespace reader {
namespace wgsl {

/// Stores tokens generated by the Lexer
class Token {
 public:
  /// The type of the parsed token
  enum class Type {
    /// Error result
    kError = -2,
    /// Uninitialized token
    kUninitialized = 0,
    /// End of input string reached
    kEOF,

    /// An identifier
    kIdentifier,
    /// A float value
    kFloatLiteral,
    /// An signed int value
    kSintLiteral,
    /// A unsigned int value
    kUintLiteral,

    /// A '&'
    kAnd,
    /// A '&&'
    kAndAnd,
    /// A '->'
    kArrow,
    /// A '@'
    kAttr,
    /// A '[[' - [DEPRECATED] now '@'
    kAttrLeft,
    /// A ']]' - [DEPRECATED] now '@'
    kAttrRight,
    /// A '/'
    kForwardSlash,
    /// A '!'
    kBang,
    /// A '['
    kBracketLeft,
    /// A ']'
    kBracketRight,
    /// A '{'
    kBraceLeft,
    /// A '}'
    kBraceRight,
    /// A ':'
    kColon,
    /// A ','
    kComma,
    /// A '='
    kEqual,
    /// A '=='
    kEqualEqual,
    /// A '>'
    kGreaterThan,
    /// A '>='
    kGreaterThanEqual,
    /// A '>>'
    kShiftRight,
    /// A '<'
    kLessThan,
    /// A '<='
    kLessThanEqual,
    /// A '<<'
    kShiftLeft,
    /// A '%'
    kMod,
    /// A '-'
    kMinus,
    /// A '--'
    kMinusMinus,
    /// A '!='
    kNotEqual,
    /// A '.'
    kPeriod,
    /// A '+'
    kPlus,
    /// A '++'
    kPlusPlus,
    /// A '|'
    kOr,
    /// A '||'
    kOrOr,
    /// A '('
    kParenLeft,
    /// A ')'
    kParenRight,
    /// A ';'
    kSemicolon,
    /// A '*'
    kStar,
    /// A '~'
    kTilde,
    /// A '_'
    kUnderscore,
    /// A '^'
    kXor,

    /// A 'array'
    kArray,
    /// A 'atomic'
    kAtomic,
    /// A 'bitcast'
    kBitcast,
    /// A 'bool'
    kBool,
    /// A 'break'
    kBreak,
    /// A 'case'
    kCase,
    /// A 'continue'
    kContinue,
    /// A 'continuing'
    kContinuing,
    /// A 'discard'
    kDiscard,
    /// A 'default'
    kDefault,
    /// A 'else'
    kElse,
    /// A 'elseif'
    kElseIf,
    /// A 'f32'
    kF32,
    /// A 'fallthrough'
    kFallthrough,
    /// A 'false'
    kFalse,
    /// A 'fn'
    kFn,
    // A 'for'
    kFor,
    /// A 'function'
    kFunction,
    /// A 'i32'
    kI32,
    /// A 'if'
    kIf,
    /// A 'import'
    kImport,
    /// A 'let'
    kLet,
    /// A 'loop'
    kLoop,
    /// A 'mat2x2'
    kMat2x2,
    /// A 'mat2x3'
    kMat2x3,
    /// A 'mat2x4'
    kMat2x4,
    /// A 'mat3x2'
    kMat3x2,
    /// A 'mat3x3'
    kMat3x3,
    /// A 'mat3x4'
    kMat3x4,
    /// A 'mat4x2'
    kMat4x2,
    /// A 'mat4x3'
    kMat4x3,
    /// A 'mat4x4'
    kMat4x4,
    /// A 'override'
    kOverride,
    /// A 'private'
    kPrivate,
    /// A 'ptr'
    kPtr,
    /// A 'return'
    kReturn,
    /// A 'sampler'
    kSampler,
    /// A 'sampler_comparison'
    kComparisonSampler,
    /// A 'storage'
    kStorage,
    /// A 'struct'
    kStruct,
    /// A 'switch'
    kSwitch,
    /// A 'texture_depth_2d'
    kTextureDepth2d,
    /// A 'texture_depth_2d_array'
    kTextureDepth2dArray,
    /// A 'texture_depth_cube'
    kTextureDepthCube,
    /// A 'texture_depth_cube_array'
    kTextureDepthCubeArray,
    /// A 'texture_depth_multisampled_2d'
    kTextureDepthMultisampled2d,
    /// A 'texture_external'
    kTextureExternal,
    /// A 'texture_multisampled_2d'
    kTextureMultisampled2d,
    /// A 'texture_1d'
    kTextureSampled1d,
    /// A 'texture_2d'
    kTextureSampled2d,
    /// A 'texture_2d_array'
    kTextureSampled2dArray,
    /// A 'texture_3d'
    kTextureSampled3d,
    /// A 'texture_cube'
    kTextureSampledCube,
    /// A 'texture_cube_array'
    kTextureSampledCubeArray,
    /// A 'texture_storage_1d'
    kTextureStorage1d,
    /// A 'texture_storage_2d'
    kTextureStorage2d,
    /// A 'texture_storage_2d_array'
    kTextureStorage2dArray,
    /// A 'texture_storage_3d'
    kTextureStorage3d,
    /// A 'true'
    kTrue,
    /// A 'type'
    kType,
    /// A 'u32'
    kU32,
    /// A 'uniform'
    kUniform,
    /// A 'var'
    kVar,
    /// A 'vec2'
    kVec2,
    /// A 'vec3'
    kVec3,
    /// A 'vec4'
    kVec4,
    /// A 'workgroup'
    kWorkgroup,
  };

  /// Converts a token type to a name
  /// @param type the type to convert
  /// @returns the token type as as string
  static std::string_view TypeToName(Type type);

  /// Creates an uninitialized token
  Token();
  /// Create a Token
  /// @param type the Token::Type of the token
  /// @param source the source of the token
  Token(Type type, const Source& source);

  /// Create a string Token
  /// @param type the Token::Type of the token
  /// @param source the source of the token
  /// @param view the source string view for the token
  Token(Type type, const Source& source, const std::string_view& view);
  /// Create a string Token
  /// @param type the Token::Type of the token
  /// @param source the source of the token
  /// @param str the source string for the token
  Token(Type type, const Source& source, const std::string& str);
  /// Create a string Token
  /// @param type the Token::Type of the token
  /// @param source the source of the token
  /// @param str the source string for the token
  Token(Type type, const Source& source, const char* str);
  /// Create a unsigned integer Token
  /// @param source the source of the token
  /// @param val the source unsigned for the token
  Token(const Source& source, uint32_t val);
  /// Create a signed integer Token
  /// @param source the source of the token
  /// @param val the source integer for the token
  Token(const Source& source, int32_t val);
  /// Create a float Token
  /// @param source the source of the token
  /// @param val the source float for the token
  Token(const Source& source, float val);
  /// Move constructor
  Token(Token&&);
  /// Copy constructor
  Token(const Token&);
  ~Token();

  /// Assignment operator
  /// @param b the token to copy
  /// @return Token
  Token& operator=(const Token& b);

  /// Equality operator with an identifier
  /// @param ident the identifier string
  /// @return true if this token is an identifier and is equal to ident.
  bool operator==(std::string_view ident);

  /// Returns true if the token is of the given type
  /// @param t the type to check against.
  /// @returns true if the token is of type `t`
  bool Is(Type t) const { return type_ == t; }

  /// @returns true if the token is uninitialized
  bool IsUninitialized() const { return type_ == Type::kUninitialized; }
  /// @returns true if the token is EOF
  bool IsEof() const { return type_ == Type::kEOF; }
  /// @returns true if the token is Error
  bool IsError() const { return type_ == Type::kError; }
  /// @returns true if the token is an identifier
  bool IsIdentifier() const { return type_ == Type::kIdentifier; }
  /// @returns true if the token is a literal
  bool IsLiteral() const {
    return type_ == Type::kSintLiteral || type_ == Type::kFalse ||
           type_ == Type::kUintLiteral || type_ == Type::kTrue ||
           type_ == Type::kFloatLiteral;
  }
  /// @returns true if token is a 'matNxM'
  bool IsMatrix() const {
    return type_ == Type::kMat2x2 || type_ == Type::kMat2x3 ||
           type_ == Type::kMat2x4 || type_ == Type::kMat3x2 ||
           type_ == Type::kMat3x3 || type_ == Type::kMat3x4 ||
           type_ == Type::kMat4x2 || type_ == Type::kMat4x3 ||
           type_ == Type::kMat4x4;
  }
  /// @returns true if token is a 'mat3xM'
  bool IsMat3xN() const {
    return type_ == Type::kMat3x2 || type_ == Type::kMat3x3 ||
           type_ == Type::kMat3x4;
  }
  /// @returns true if token is a 'mat4xM'
  bool IsMat4xN() const {
    return type_ == Type::kMat4x2 || type_ == Type::kMat4x3 ||
           type_ == Type::kMat4x4;
  }
  /// @returns true if token is a 'matNx3'
  bool IsMatNx3() const {
    return type_ == Type::kMat2x3 || type_ == Type::kMat3x3 ||
           type_ == Type::kMat4x3;
  }
  /// @returns true if token is a 'matNx4'
  bool IsMatNx4() const {
    return type_ == Type::kMat2x4 || type_ == Type::kMat3x4 ||
           type_ == Type::kMat4x4;
  }

  /// @returns true if token is a 'vecN'
  bool IsVector() const {
    return type_ == Type::kVec2 || type_ == Type::kVec3 || type_ == Type::kVec4;
  }

  /// @returns the source information for this token
  Source source() const { return source_; }

  /// Returns the string value of the token
  /// @return std::string
  std::string to_str() const;
  /// Returns the float value of the token. 0 is returned if the token does not
  /// contain a float value.
  /// @return float
  float to_f32() const;
  /// Returns the uint32 value of the token. 0 is returned if the token does not
  /// contain a unsigned integer value.
  /// @return uint32_t
  uint32_t to_u32() const;
  /// Returns the int32 value of the token. 0 is returned if the token does not
  /// contain a signed integer value.
  /// @return int32_t
  int32_t to_i32() const;

  /// @returns the token type as string
  std::string_view to_name() const { return Token::TypeToName(type_); }

 private:
  /// The Token::Type of the token
  Type type_ = Type::kError;
  /// The source where the token appeared
  Source source_;
  /// The value represented by the token
  std::variant<int32_t, uint32_t, float, std::string, std::string_view> value_;
};

#ifndef NDEBUG
inline std::ostream& operator<<(std::ostream& out, Token::Type type) {
  out << Token::TypeToName(type);
  return out;
}
#endif  // NDEBUG

}  // namespace wgsl
}  // namespace reader
}  // namespace tint

#endif  // SRC_TINT_READER_WGSL_TOKEN_H_