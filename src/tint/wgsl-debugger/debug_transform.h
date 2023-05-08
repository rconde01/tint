#pragma once

#include "src/tint/transform/transform.h"

namespace tint {
class CloneContext;
}

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