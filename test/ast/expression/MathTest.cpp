#include "MathExpression.hpp"
#include "MathTermExpression.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(math_expression, calculate) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto factorExp1 = std::make_shared<MathFactorExpression>(var1);

    auto var2 = std::make_shared<Variable>(std::vector<int>{3,2,1});
    auto factorExp2 =  std::make_shared<MathFactorExpression>(var2);

    std::vector<std::shared_ptr<Expression>> factorExps{factorExp1, factorExp2};

    MathExpression plusExpr(factorExps, std::vector<TokenType>{TokenType::Plus});
    ASSERT_EQ(plusExpr.calculate(), *var1 + *var2);

    MathExpression minusExp(factorExps, std::vector<TokenType>{TokenType::Minus});
    ASSERT_EQ(minusExp.calculate(), *var1 - *var2);
}

TEST(math_expression, compound_calculate) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto factorExp1 = std::make_shared<MathFactorExpression>(var1);

    auto var2 = std::make_shared<Variable>(std::vector<int>{3,2,1});
    auto factorExp2 =  std::make_shared<MathFactorExpression>(var2);

    std::vector<std::shared_ptr<Expression>> expPart1{factorExp1, factorExp2};
    auto termExp1 = std::make_shared<MathTermExpression>(expPart1, std::vector<TokenType>{TokenType::Divide});

    std::vector<std::shared_ptr<Expression>> expPart2{factorExp2, factorExp1};
    auto termExp2 = std::make_shared<MathTermExpression>(expPart2, std::vector<TokenType>{TokenType::VectorMultiply});

    MathExpression mathExp{{termExp1, termExp2}, {TokenType::Minus}};
    ASSERT_EQ(mathExp.calculate(), *var1 / *var2 - var2->vectorProduct(*var1));
}