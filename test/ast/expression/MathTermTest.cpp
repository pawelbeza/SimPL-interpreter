#include "MathTermExpression.hpp"
#include "Variable.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(math_term_expression, calculate) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto factorExp1 = std::make_shared<MathFactorExpression>(var1);

    auto var2 = std::make_shared<Variable>(std::vector<int>{3,2,1});
    auto factorExp2 =  std::make_shared<MathFactorExpression>(var2);

    std::vector<std::shared_ptr<Expression>> factorExps{factorExp1, factorExp2};

    MathTermExpression scalarMultiplyExp(factorExps, std::vector<TokenType>{TokenType::ScalarMultiply});
    ASSERT_EQ(scalarMultiplyExp.calculate(), *var1 * *var2);

    MathTermExpression vectorMultiplyExp(factorExps, std::vector<TokenType>{TokenType::VectorMultiply});
    ASSERT_EQ(vectorMultiplyExp.calculate(), var1->vectorProduct(*var2));

    MathTermExpression divideExp(factorExps, std::vector<TokenType>{TokenType::Divide});
    ASSERT_EQ(divideExp.calculate(), *var1 / *var2);

    MathTermExpression moduloExp(factorExps, std::vector<TokenType>{TokenType::Modulo});
    ASSERT_EQ(moduloExp.calculate(), *var1 % *var2);
}