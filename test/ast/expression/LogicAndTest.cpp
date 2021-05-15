#include "AndExpression.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(and_expression, calculate) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto mathExpr1 =  std::make_shared<MathFactorExpression>(var1);

    auto var2 = std::make_shared<Variable>(std::vector<int>{3,2,3});
    auto mathExpr2 =  std::make_shared<MathFactorExpression>(var2);

    std::vector<std::shared_ptr<Expression>> baseExps1({mathExpr1, mathExpr2});

    auto andExp1 = AndExpression(baseExps1);
    ASSERT_TRUE(andExp1.calculate());

    auto var3 = std::make_shared<Variable>(std::vector<int>{0});
    auto mathExpr3 =  std::make_shared<MathFactorExpression>(var3);

    std::vector<std::shared_ptr<Expression>> baseExps2({mathExpr1, mathExpr3});

    auto andExp2 = AndExpression(baseExps2);
    ASSERT_FALSE(andExp2.calculate());
}
