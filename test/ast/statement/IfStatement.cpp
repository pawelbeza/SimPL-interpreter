#include "IfStatement.hpp"
#include <MathFactorExpression.hpp>
#include <ReturnStatement.hpp>

#include "gtest/gtest.h"

using namespace simpl;

// if (1) {return 1;}
TEST(conditional_statement, if_statement_successful) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{1});
    auto condExp = std::make_shared<MathFactorExpression>(var1);

    auto ifBlock = std::make_shared<Block>();
    auto ret = ifBlock->execute();
    ASSERT_EQ(ret.type, Return::Type::None);

    auto retStatement = std::make_shared<ReturnStatement>(condExp);
    ifBlock->addStatement(retStatement);

    auto ifStatement = std::make_shared<IfStatement>(condExp, ifBlock);
    ret = ifStatement->execute();

    ASSERT_EQ(ret.type, Return::Type::Variable);
    ASSERT_EQ(ret.var, *var1);
}

// if (0) {return 0;}
TEST(conditional_statement, if_statement_failed) {
    auto var1 = std::make_shared<Variable>(std::vector<int>{0});
    auto condExp = std::make_shared<MathFactorExpression>(var1);

    auto ifBlock = std::make_shared<Block>();
    auto ret = ifBlock->execute();
    ASSERT_EQ(ret.type, Return::Type::None);

    auto retStatement = std::make_shared<ReturnStatement>(condExp);
    ifBlock->addStatement(retStatement);

    auto ifStatement = std::make_shared<IfStatement>(condExp, ifBlock);
    ret = ifStatement->execute();
    ASSERT_EQ(ret.type, Return::Type::None);
}

// if (1) {return 1} else {return 0}
TEST(conditional_statement, if_else_statement_if_successful) {
    auto ifVar = std::make_shared<Variable>(std::vector<int>{1});
    auto ifCondExp = std::make_shared<MathFactorExpression>(ifVar);
    auto ifBlock = std::make_shared<Block>();

    auto ifRetStatement = std::make_shared<ReturnStatement>(ifCondExp);
    ifBlock->addStatement(ifRetStatement);

    auto elseVar = std::make_shared<Variable>(std::vector<int>{0});
    auto elseCondExp = std::make_shared<MathFactorExpression>(elseVar);
    auto elseBlock = std::make_shared<Block>();

    auto elseRetStatement = std::make_shared<ReturnStatement>(elseCondExp);
    elseBlock->addStatement(elseRetStatement);

    auto statement = std::make_shared<IfStatement>(ifCondExp, ifBlock, elseBlock);
    auto ret = statement->execute();

    ASSERT_EQ(ret.type, Return::Type::Variable);
    ASSERT_EQ(ret.var, Variable({1}));
}

// if (0) {return 0} else {return 1}
TEST(conditional_statement, if_else_statement_else_successful) {
    auto ifVar = std::make_shared<Variable>(std::vector<int>{0});
    auto ifCondExp = std::make_shared<MathFactorExpression>(ifVar);
    auto ifBlock = std::make_shared<Block>();

    auto ifRetStatement = std::make_shared<ReturnStatement>(ifCondExp);
    ifBlock->addStatement(ifRetStatement);

    auto elseVar = std::make_shared<Variable>(std::vector<int>{1});
    auto elseCondExp = std::make_shared<MathFactorExpression>(elseVar);
    auto elseBlock = std::make_shared<Block>();

    auto elseRetStatement = std::make_shared<ReturnStatement>(elseCondExp);
    elseBlock->addStatement(elseRetStatement);

    auto statement = std::make_shared<IfStatement>(ifCondExp, ifBlock, elseBlock);
    auto ret = statement->execute();

    ASSERT_EQ(ret.type, Return::Type::Variable);
    ASSERT_EQ(ret.var, Variable({1}));
}