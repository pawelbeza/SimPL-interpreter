#include "ReturnStatement.hpp"

#include <gtest/gtest.h>
#include <MathFactorExpression.hpp>

using namespace simpl;


TEST(return_statement, none) {
    ReturnStatement returnStatement;

    auto ret = returnStatement.execute();
    ASSERT_EQ(ret.type, Return::Type::None);
}

// return 1;
TEST(return_statement, variable) {
    auto var = std::make_shared<Variable>(std::vector<int>{1});
    auto exp = std::make_shared<MathFactorExpression>(var);
    ReturnStatement returnStatement(exp);

    auto ret = returnStatement.execute();
    ASSERT_EQ(ret.type, Return::Type::Variable);
    ASSERT_EQ(ret.var, Variable({1}));
}