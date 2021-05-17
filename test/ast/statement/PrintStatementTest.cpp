#include "PrintStatement.hpp"

#include <gtest/gtest.h>
#include <MathFactorExpression.hpp>

using namespace simpl;

// print("hello");
TEST(print, string) {
    std::stringstream ss;
    PrintStatement statement(ss);

    statement.addPrintArg("hello");
    ASSERT_EQ(statement.execute().type, Return::Type::None);
    ASSERT_EQ(ss.str(), "hello");
}

// print([1,2,3])
TEST(print, variable) {
    std::stringstream ss;
    PrintStatement statement(ss);

    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto exp = std::make_shared<MathFactorExpression>(var);
    statement.addPrintArg(exp);

    ASSERT_EQ(statement.execute().type, Return::Type::None);
    ASSERT_EQ(ss.str(), "[1, 2, 3]");
}

// print("vector", [1,2,3], "\n");
TEST(print, compound) {
    std::stringstream ss;
    PrintStatement statement(ss);

    statement.addPrintArg("vector: ");

    auto var = std::make_shared<Variable>(std::vector<int>{1,2,3});
    auto exp = std::make_shared<MathFactorExpression>(var);
    statement.addPrintArg(exp);

    statement.addPrintArg("\n");

    ASSERT_EQ(statement.execute().type, Return::Type::None);
    ASSERT_EQ(ss.str(), "vector: [1, 2, 3]\n");
}