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

#include <sstream>

#include "src/tint/ir/instruction.h"
#include "src/tint/ir/test_helper.h"

namespace tint::ir {
namespace {

using IR_InstructionTest = TestHelper;

TEST_F(IR_InstructionTest, CreateAnd) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.And(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kAnd);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 & 2");
}

TEST_F(IR_InstructionTest, CreateOr) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Or(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kOr);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 | 2");
}

TEST_F(IR_InstructionTest, CreateXor) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Xor(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kXor);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 ^ 2");
}

TEST_F(IR_InstructionTest, CreateLogicalAnd) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.LogicalAnd(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kLogicalAnd);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 && 2");
}

TEST_F(IR_InstructionTest, CreateLogicalOr) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.LogicalOr(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kLogicalOr);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 || 2");
}

TEST_F(IR_InstructionTest, CreateEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Equal(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kEqual);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 == 2");
}

TEST_F(IR_InstructionTest, CreateNotEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.NotEqual(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kNotEqual);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 != 2");
}

TEST_F(IR_InstructionTest, CreateLessThan) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.LessThan(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kLessThan);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 < 2");
}

TEST_F(IR_InstructionTest, CreateGreaterThan) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.GreaterThan(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kGreaterThan);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 > 2");
}

TEST_F(IR_InstructionTest, CreateLessThanEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.LessThanEqual(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kLessThanEqual);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 <= 2");
}

TEST_F(IR_InstructionTest, CreateGreaterThanEqual) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.GreaterThanEqual(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kGreaterThanEqual);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 >= 2");
}

TEST_F(IR_InstructionTest, CreateShiftLeft) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.ShiftLeft(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kShiftLeft);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 << 2");
}

TEST_F(IR_InstructionTest, CreateShiftRight) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.ShiftRight(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kShiftRight);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 >> 2");
}

TEST_F(IR_InstructionTest, CreateAdd) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Add(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kAdd);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 + 2");
}

TEST_F(IR_InstructionTest, CreateSubtract) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Subtract(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kSubtract);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 - 2");
}

TEST_F(IR_InstructionTest, CreateMultiply) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Multiply(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kMultiply);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 * 2");
}

TEST_F(IR_InstructionTest, CreateDivide) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Divide(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kDivide);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 / 2");
}

TEST_F(IR_InstructionTest, CreateModulo) {
    auto& b = CreateEmptyBuilder();

    b.builder.next_value_id = Value::Id(42);
    auto instr = b.builder.Modulo(Value(i32(4)), Value(i32(2)));

    EXPECT_EQ(instr.GetKind(), Instruction::Kind::kModulo);

    ASSERT_TRUE(instr.Result().IsTemp());
    EXPECT_EQ(Value::Id(42), instr.Result().AsId());

    ASSERT_TRUE(instr.HasLHS());
    auto& lhs = instr.LHS();
    ASSERT_TRUE(lhs.IsI32());
    EXPECT_EQ(i32(4), lhs.AsI32());

    ASSERT_TRUE(instr.HasRHS());
    auto& rhs = instr.RHS();
    ASSERT_TRUE(rhs.IsI32());
    EXPECT_EQ(i32(2), rhs.AsI32());

    std::stringstream str;
    str << instr;
    EXPECT_EQ(str.str(), "%42 = 4 % 2");
}

}  // namespace
}  // namespace tint::ir
