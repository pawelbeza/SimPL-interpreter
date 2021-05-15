#include "LogicExpression.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(logic_expression, calculate) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto factorExp1 = std::make_shared<MathFactorExpression>(var1);

    auto var2 = std::make_shared<Variable>(std::vector<int>{3,2,1});
    auto factorExp2 =  std::make_shared<MathFactorExpression>(var2);

    std::vector<std::shared_ptr<Expression>> exps1({factorExp1, factorExp2});

    LogicExpression logicExp1(exps1);
    ASSERT_TRUE(logicExp1.calculate());

    auto var3 = std::make_shared<Variable>(std::vector<int>{0});
    auto factorExp3 =  std::make_shared<MathFactorExpression>(var3);

    std::vector<std::shared_ptr<Expression>> exps2({factorExp1, factorExp3});

    LogicExpression logicExp2(exps2);
    ASSERT_TRUE(logicExp2.calculate());

    std::vector<std::shared_ptr<Expression>> exps3({factorExp3, factorExp3});

    LogicExpression logicExp3(exps3);
    ASSERT_FALSE(logicExp3.calculate());
}

TEST(logic_expression, compound_calculate) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto factorExp1 = std::make_shared<MathFactorExpression>(var1);

    auto var2 = std::make_shared<Variable>(std::vector<int>{3,2,1});
    auto factorExp2 =  std::make_shared<MathFactorExpression>(var2);

    auto var3 = std::make_shared<Variable>(std::vector<int>{0});
    auto factorExp3 =  std::make_shared<MathFactorExpression>(var3);

    std::vector<std::shared_ptr<Expression>> expPart1{factorExp1, factorExp2};
    auto andExp1 = std::make_shared<AndExpression>(expPart1);

    std::vector<std::shared_ptr<Expression>> expPart2{factorExp3, factorExp3};
    auto andExp2 = std::make_shared<AndExpression>(expPart2);

    std::vector<std::shared_ptr<Expression>> exps1({andExp1, andExp2});
    LogicExpression logicExp1(exps1);
    ASSERT_TRUE(logicExp1.calculate());

    std::vector<std::shared_ptr<Expression>> exps2({andExp2, andExp2});
    LogicExpression logicExp2(exps2);
    ASSERT_FALSE(logicExp2.calculate());
}