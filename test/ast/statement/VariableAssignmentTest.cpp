#include "VariableAssignment.hpp"

#include <gtest/gtest.h>
#include <MathFactorExpression.hpp>

using namespace simpl;

// a := [1,2,3]; a = [3,2,1];
TEST(assignment, variable) {
    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto exp = std::make_shared<MathFactorExpression>(var);

    auto assignedVar = std::make_shared<Variable>(std::vector<int>{3,2,1});
    VariableAssignment assignment(assignedVar, exp);

    ASSERT_EQ(assignment.execute().type, Return::Type::None);
    ASSERT_EQ(*var, *assignedVar);
}