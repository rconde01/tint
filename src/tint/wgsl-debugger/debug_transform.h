#pragma once

#include "src/tint/transform/transform.h"

namespace tint {
class CloneContext;
}

namespace tint::ast {
class AssignmentStatement;
}

// TODO do these type enums already exist somewhere?
enum class ExpressionType {
  i32,
  u32,
  f32,
  vec2_i32,
  vec2_u32,
  vec2_f32,
  vec3_i32,
  vec3_u32,
  vec3_f32,
  vec4_i32,
  vec4_u32,
  vec4_f32
};

struct DebugCapture {
  size_t number;
  tint::ast::Expression* expression;
  tint::ast::AssignmentStatement* assign;
  ExpressionType type;
};

struct InstrumentationData {
  std::vector<DebugCapture> captures;
};

namespace tint::transform {
class DebugTransform final : public utils::Castable<DebugTransform, Transform> {
 public:
  DebugTransform();
  ~DebugTransform() override;

  ApplyResult Apply(const Program* program,
                    const DataMap& inputs,
                    DataMap& outputs) const override;

 private:
  struct State;
};
}  // namespace tint::transform
