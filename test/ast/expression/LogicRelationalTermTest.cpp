#include "RelationalExpression.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(relational_expression, calculate) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto mathExpr1 =  std::make_shared<MathFactorExpression>(var1);

    auto var2 = std::make_shared<Variable>(std::vector<int>{3,2,3});
    auto mathExpr2 =  std::make_shared<MathFactorExpression>(var2);

    std::vector<std::shared_ptr<Expression>> baseExps({mathExpr1, mathExpr2});

    auto equalityExp = RelationalExpression(baseExps, std::vector<TokenType>{TokenType::Equality});
    ASSERT_FALSE(equalityExp.calculate());

    auto inequalityExp = RelationalExpression(baseExps, std::vector<TokenType>{TokenType::Inequality});
    ASSERT_TRUE(inequalityExp.calculate());

    auto lessExp = RelationalExpression(baseExps, std::vector<TokenType>{TokenType::Less});
    ASSERT_TRUE(lessExp.calculate());

    auto lessOrEqualExp = RelationalExpression(baseExps, std::vector<TokenType>{TokenType::LessOrEqual});
    ASSERT_TRUE(lessOrEqualExp.calculate());

    auto greaterExp = RelationalExpression(baseExps, std::vector<TokenType>{TokenType::Greater});
    ASSERT_FALSE(greaterExp.calculate());

    auto greaterOrEqualExp = RelationalExpression(baseExps, std::vector<TokenType>{TokenType::GreaterOrEqual});
    ASSERT_FALSE(greaterExp.calculate());
}