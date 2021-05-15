#include "MathFactorExpression.hpp"
#include "Variable.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(math_factor, variable) {
    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    MathFactorExpression exp(var);
    ASSERT_EQ(exp.calculate(), Variable({1,2,3}));
}

TEST(math_factor, minus_variable) {
    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    MathFactorExpression exp(var, true);
    ASSERT_EQ(exp.calculate(), Variable({-1,-2,-3}));
}

TEST(math_factor, expression) {
    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto nextExp = std::make_shared<MathFactorExpression>(var);

    MathFactorExpression exp(nextExp);
    ASSERT_EQ(exp.calculate(), Variable({1,2,3}));
}

TEST(math_factor, minus_expression) {
    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto nextExp = std::make_shared<MathFactorExpression>(var);

    MathFactorExpression exp(nextExp, true);
    ASSERT_EQ(exp.calculate(), Variable({-1,-2,-3}));
}
