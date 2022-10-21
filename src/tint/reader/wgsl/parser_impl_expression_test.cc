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

#include "src/tint/reader/wgsl/parser_impl_test_helper.h"

namespace tint::reader::wgsl {
namespace {

TEST_F(ParserImplTest, Expression_InvalidLHS) {
    auto p = parser("if (a) {} || true");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    EXPECT_EQ(e.value, nullptr);
}

TEST_F(ParserImplTest, Expression_Or_Parses) {
    auto p = parser("a || true");
    auto e = p->expression();
    EXPECT_TRUE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    ASSERT_NE(e.value, nullptr);

    EXPECT_EQ(e->source.range.begin.line, 1u);
    EXPECT_EQ(e->source.range.begin.column, 3u);
    EXPECT_EQ(e->source.range.end.line, 1u);
    EXPECT_EQ(e->source.range.end.column, 5u);

    ASSERT_TRUE(e->Is<ast::BinaryExpression>());
    auto* rel = e->As<ast::BinaryExpression>();
    EXPECT_EQ(ast::BinaryOp::kLogicalOr, rel->op);

    ASSERT_TRUE(rel->lhs->Is<ast::IdentifierExpression>());
    auto* ident = rel->lhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("a"));

    ASSERT_TRUE(rel->rhs->Is<ast::BoolLiteralExpression>());
    ASSERT_TRUE(rel->rhs->As<ast::BoolLiteralExpression>()->value);
}

TEST_F(ParserImplTest, Expression_Or_Parses_Multiple) {
    auto p = parser("a || true || b");
    auto e = p->expression();
    EXPECT_TRUE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    ASSERT_NE(e.value, nullptr);

    ASSERT_TRUE(e->Is<ast::BinaryExpression>());
    // lhs: (a || true)
    // rhs: b
    auto* rel = e->As<ast::BinaryExpression>();
    EXPECT_EQ(ast::BinaryOp::kLogicalOr, rel->op);

    ASSERT_TRUE(rel->rhs->Is<ast::IdentifierExpression>());
    auto* ident = rel->rhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("b"));

    ASSERT_TRUE(rel->lhs->Is<ast::BinaryExpression>());
    // lhs: a
    // rhs: true
    rel = rel->lhs->As<ast::BinaryExpression>();
    EXPECT_EQ(ast::BinaryOp::kLogicalOr, rel->op);

    ASSERT_TRUE(rel->lhs->Is<ast::IdentifierExpression>());
    ident = rel->lhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("a"));

    ASSERT_TRUE(rel->rhs->Is<ast::BoolLiteralExpression>());
    ASSERT_TRUE(rel->rhs->As<ast::BoolLiteralExpression>()->value);
}

TEST_F(ParserImplTest, Expression_Or_InvalidRHS) {
    auto p = parser("true || if (a) {}");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_EQ(e.value, nullptr);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(p->error(), "1:9: unable to parse right side of || expression");
}

TEST_F(ParserImplTest, Expression_And_Parses) {
    auto p = parser("a && true");
    auto e = p->expression();
    EXPECT_TRUE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    ASSERT_NE(e.value, nullptr);

    EXPECT_EQ(e->source.range.begin.line, 1u);
    EXPECT_EQ(e->source.range.begin.column, 3u);
    EXPECT_EQ(e->source.range.end.line, 1u);
    EXPECT_EQ(e->source.range.end.column, 5u);

    ASSERT_TRUE(e->Is<ast::BinaryExpression>());
    auto* rel = e->As<ast::BinaryExpression>();
    EXPECT_EQ(ast::BinaryOp::kLogicalAnd, rel->op);

    ASSERT_TRUE(rel->lhs->Is<ast::IdentifierExpression>());
    auto* ident = rel->lhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("a"));

    ASSERT_TRUE(rel->rhs->Is<ast::BoolLiteralExpression>());
    ASSERT_TRUE(rel->rhs->As<ast::BoolLiteralExpression>()->value);
}

TEST_F(ParserImplTest, Expression_And_Parses_Multple) {
    auto p = parser("a && true && b");
    auto e = p->expression();
    EXPECT_TRUE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    ASSERT_NE(e.value, nullptr);

    ASSERT_TRUE(e->Is<ast::BinaryExpression>());
    // lhs: (a && true)
    // rhs: b
    auto* rel = e->As<ast::BinaryExpression>();
    EXPECT_EQ(ast::BinaryOp::kLogicalAnd, rel->op);

    ASSERT_TRUE(rel->rhs->Is<ast::IdentifierExpression>());
    auto* ident = rel->rhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("b"));

    ASSERT_TRUE(rel->lhs->Is<ast::BinaryExpression>());
    // lhs: a
    // rhs: true
    rel = rel->lhs->As<ast::BinaryExpression>();
    ASSERT_TRUE(rel->lhs->Is<ast::IdentifierExpression>());
    ident = rel->lhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("a"));

    ASSERT_TRUE(rel->rhs->Is<ast::BoolLiteralExpression>());
    ASSERT_TRUE(rel->rhs->As<ast::BoolLiteralExpression>()->value);
}

TEST_F(ParserImplTest, Expression_And_InvalidRHS) {
    auto p = parser("true && if (a) {}");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_EQ(e.value, nullptr);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(p->error(), "1:9: unable to parse right side of && expression");
}

TEST_F(ParserImplTest, Expression_Mixing_OrWithAnd) {
    auto p = parser("a && true || b");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_EQ(e.value, nullptr);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(p->error(), "1:3: mixing '&&' and '||' requires parenthesis");
}

TEST_F(ParserImplTest, Expression_Mixing_AndWithOr) {
    auto p = parser("a || true && b");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_EQ(e.value, nullptr);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(p->error(), "1:3: mixing '||' and '&&' requires parenthesis");
}

TEST_F(ParserImplTest, Expression_Bitwise) {
    auto p = parser("a & b");
    auto e = p->expression();
    EXPECT_TRUE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    ASSERT_NE(e.value, nullptr);

    ASSERT_TRUE(e->Is<ast::BinaryExpression>());
    auto* rel = e->As<ast::BinaryExpression>();
    EXPECT_EQ(ast::BinaryOp::kAnd, rel->op);

    ASSERT_TRUE(rel->lhs->Is<ast::IdentifierExpression>());
    auto* ident = rel->lhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("a"));

    ASSERT_TRUE(rel->rhs->Is<ast::IdentifierExpression>());
    ident = rel->rhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("b"));
}

TEST_F(ParserImplTest, Expression_Relational) {
    auto p = parser("a <= b");
    auto e = p->expression();
    EXPECT_TRUE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    ASSERT_NE(e.value, nullptr);

    ASSERT_TRUE(e->Is<ast::BinaryExpression>());
    auto* rel = e->As<ast::BinaryExpression>();
    EXPECT_EQ(ast::BinaryOp::kLessThanEqual, rel->op);

    ASSERT_TRUE(rel->lhs->Is<ast::IdentifierExpression>());
    auto* ident = rel->lhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("a"));

    ASSERT_TRUE(rel->rhs->Is<ast::IdentifierExpression>());
    ident = rel->rhs->As<ast::IdentifierExpression>();
    EXPECT_EQ(ident->symbol, p->builder().Symbols().Get("b"));
}

TEST_F(ParserImplTest, Expression_InvalidUnary) {
    auto p = parser("!if || true");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_EQ(e.value, nullptr);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(p->error(), "1:2: unable to parse right side of ! expression");
}

TEST_F(ParserImplTest, Expression_InvalidBitwise) {
    auto p = parser("a & if");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_EQ(e.value, nullptr);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(p->error(), "1:5: unable to parse right side of & expression");
}

TEST_F(ParserImplTest, Expression_InvalidRelational) {
    auto p = parser("a <= if");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_EQ(e.value, nullptr);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(p->error(), "1:6: unable to parse right side of <= expression");
}

TEST_F(ParserImplTest, Expression_Associativity) {
    auto p = parser("1 < 2 || 2 < 3");
    auto e = p->expression();
    EXPECT_TRUE(e.matched);
    EXPECT_FALSE(e.errored);
    EXPECT_FALSE(p->has_error()) << p->error();
    ASSERT_NE(e.value, nullptr);
}

TEST_F(ParserImplTest, Expression_InvalidAssociativity) {
    auto p = parser("1 < 2 && 2 < 3 || 3 < 4");
    auto e = p->expression();
    EXPECT_FALSE(e.matched);
    EXPECT_TRUE(e.errored);
    EXPECT_TRUE(p->has_error());
    EXPECT_EQ(e.value, nullptr);
    EXPECT_EQ(p->error(), R"(1:7: mixing '&&' and '||' requires parenthesis)");
}

namespace mixing_binary_ops {

struct BinaryOperatorInfo {
    // A uint64_t with a single bit assigned that uniquely identifies the binary-op.
    uint64_t bit;
    // The WGSL operator symbol. Example: '<='
    const char* symbol;
    // A bit mask of all operators that can immediately follow the RHS of this operator without
    // requiring parentheses. In other words, `can_follow_without_paren` is the full set of
    // operators that can substitute `<next-operator>` in the WGSL:
    //   `expr_a <this-operator> expr_b <next-operator> expr_c`
    // without requiring additional parentheses.
    uint64_t can_follow_without_paren;
};

// Each binary operator is given a unique bit in a uint64_t
static constexpr uint64_t kOpMul = static_cast<uint64_t>(1) << 0;
static constexpr uint64_t kOpDiv = static_cast<uint64_t>(1) << 1;
static constexpr uint64_t kOpMod = static_cast<uint64_t>(1) << 2;
static constexpr uint64_t kOpAdd = static_cast<uint64_t>(1) << 3;
static constexpr uint64_t kOpSub = static_cast<uint64_t>(1) << 4;
static constexpr uint64_t kOpBAnd = static_cast<uint64_t>(1) << 5;
static constexpr uint64_t kOpBOr = static_cast<uint64_t>(1) << 6;
static constexpr uint64_t kOpBXor = static_cast<uint64_t>(1) << 7;
static constexpr uint64_t kOpShl = static_cast<uint64_t>(1) << 8;
static constexpr uint64_t kOpShr = static_cast<uint64_t>(1) << 9;
static constexpr uint64_t kOpLt = static_cast<uint64_t>(1) << 10;
static constexpr uint64_t kOpGt = static_cast<uint64_t>(1) << 11;
static constexpr uint64_t kOpLe = static_cast<uint64_t>(1) << 12;
static constexpr uint64_t kOpGe = static_cast<uint64_t>(1) << 13;
static constexpr uint64_t kOpEq = static_cast<uint64_t>(1) << 14;
static constexpr uint64_t kOpNe = static_cast<uint64_t>(1) << 15;
static constexpr uint64_t kOpLAnd = static_cast<uint64_t>(1) << 16;
static constexpr uint64_t kOpLOr = static_cast<uint64_t>(1) << 17;

// Bit mask for the binary operator groups
static constexpr uint64_t kMultiplicative = kOpMul | kOpDiv | kOpMod;
static constexpr uint64_t kAdditive = kOpAdd | kOpSub;
static constexpr uint64_t kShift = kOpShl | kOpShr;
static constexpr uint64_t kRelational = kOpLt | kOpGt | kOpLe | kOpGe | kOpEq | kOpNe;
static constexpr uint64_t kLogical = kOpLAnd | kOpLOr;

// The binary operator table
static constexpr const BinaryOperatorInfo kBinaryOperators[] = {
    // multiplicative
    {kOpMul, "*", kLogical | kRelational | kAdditive | kMultiplicative},
    {kOpDiv, "/", kLogical | kRelational | kAdditive | kMultiplicative},
    {kOpMod, "%", kLogical | kRelational | kAdditive | kMultiplicative},
    // additive
    {kOpAdd, "+", kLogical | kRelational | kAdditive | kMultiplicative},
    {kOpSub, "-", kLogical | kRelational | kAdditive | kMultiplicative},
    // bitwise
    {kOpBAnd, "&", kOpBAnd},
    {kOpBOr, "|", kOpBOr},
    {kOpBXor, "^", kOpBXor},
    // shift
    {kOpShl, "<<", kLogical | kRelational},
    {kOpShr, ">>", kLogical | kRelational},
    // relational
    {kOpLt, "<", kLogical | kShift | kAdditive | kMultiplicative},
    {kOpGt, ">", kLogical | kShift | kAdditive | kMultiplicative},
    {kOpLe, "<=", kLogical | kShift | kAdditive | kMultiplicative},
    {kOpGe, ">=", kLogical | kShift | kAdditive | kMultiplicative},
    {kOpEq, "==", kLogical | kShift | kAdditive | kMultiplicative},
    {kOpNe, "!=", kLogical | kShift | kAdditive | kMultiplicative},
    // logical
    {kOpLAnd, "&&", kOpLAnd | kRelational | kShift | kAdditive | kMultiplicative},
    {kOpLOr, "||", kOpLOr | kRelational | kShift | kAdditive | kMultiplicative},
};

struct Case {
    BinaryOperatorInfo lhs_op;
    BinaryOperatorInfo rhs_op;
    bool should_parse;
};

static std::ostream& operator<<(std::ostream& o, const Case& c) {
    return o << "a " << c.lhs_op.symbol << " b " << c.rhs_op.symbol << " c ";
}

static std::vector<Case> Cases() {
    std::vector<Case> out;
    for (auto& lhs_op : kBinaryOperators) {
        for (auto& rhs_op : kBinaryOperators) {
            bool should_parse = lhs_op.can_follow_without_paren & rhs_op.bit;
            out.push_back({lhs_op, rhs_op, should_parse});
        }
    }
    return out;
}

using ParserImplMixedBinaryOpTest = ParserImplTestWithParam<Case>;

TEST_P(ParserImplMixedBinaryOpTest, Test) {
    std::stringstream wgsl;
    wgsl << GetParam();
    auto p = parser(wgsl.str());
    auto e = p->expression();
    if (GetParam().should_parse) {
        ASSERT_TRUE(e.matched) << e.errored;
        EXPECT_TRUE(e->Is<ast::BinaryExpression>());
    } else {
        EXPECT_FALSE(e.matched);
        EXPECT_TRUE(e.errored);
        EXPECT_EQ(e.value, nullptr);
        EXPECT_TRUE(p->has_error());
        std::stringstream expected;
        expected << "1:3: mixing '" << GetParam().lhs_op.symbol << "' and '"
                 << GetParam().rhs_op.symbol << "' requires parenthesis";
        EXPECT_EQ(p->error(), expected.str());
    }
}
INSTANTIATE_TEST_SUITE_P(ParserImplMixedBinaryOpTest,
                         ParserImplMixedBinaryOpTest,
                         testing::ValuesIn(Cases()));

}  // namespace mixing_binary_ops

}  // namespace
}  // namespace tint::reader::wgsl
