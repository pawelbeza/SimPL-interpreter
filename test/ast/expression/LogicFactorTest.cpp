#include "LogicFactorExpression.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(logic_factor, calculate) {
    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto mathExpr =  std::make_shared<MathFactorExpression>(var);

    auto factor = LogicFactorExpression(mathExpr);
    ASSERT_TRUE(factor.calculate());
    ASSERT_EQ(factor.calculate(), Variable({1,2,3}));
}

TEST(logic_factor, negation_calculate) {
    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto mathExpr =  std::make_shared<MathFactorExpression>(var);

    auto factor = LogicFactorExpression(mathExpr, true);
    ASSERT_FALSE(factor.calculate());
    ASSERT_EQ(factor.calculate(), Variable({0}));
}