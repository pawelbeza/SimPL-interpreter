#include "WhileStatement.hpp"
#include <MathFactorExpression.hpp>
#include <RelationalExpression.hpp>
#include <VariableAssignment.hpp>

#include <gtest/gtest.h>

using namespace simpl;

// i:= 0; while(i < 5) {i = i + 1;}
TEST(while_statement, execute) {
    auto var = std::make_shared<Variable>(std::vector<int>{0});
    auto baseExp = std::make_shared<MathFactorExpression>(var);

    auto target = std::make_shared<Variable>(std::vector<int>{5});
    auto targetExp = std::make_shared<MathFactorExpression>(target);

    auto exps = std::vector<std::shared_ptr<Expression>>({baseExp, targetExp});
    auto relExp = std::make_shared<RelationalExpression>(exps, std::vector<TokenType>{TokenType::Less});

    auto addVar = std::make_shared<Variable>(std::vector<int>{1});
    auto addExp = std::make_shared<MathFactorExpression>(addVar);

    auto mathComponents = std::vector<std::shared_ptr<Expression>>{baseExp, addExp};
    auto mathExp = std::make_shared<MathExpression>(mathComponents, std::vector<TokenType>{TokenType::Plus});

    auto assignment = std::make_shared<VariableAssignment>(var, mathExp);
    auto block = std::make_shared<Block>(std::make_shared<Block>(), std::vector<std::shared_ptr<Statement>>{assignment}, std::unordered_map<std::string, std::shared_ptr<Variable>>{});

    WhileStatement whileStatement(relExp, block);

    ASSERT_EQ(whileStatement.execute().type, Return::Type::None);
    ASSERT_EQ(*var, Variable({5}));
}