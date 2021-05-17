#include "Variable.hpp"

#include <gtest/gtest.h>

using namespace simpl;

TEST(ast_variable, empty_variable) {
    Variable var1 = Variable();
    Variable var2 = var1;

    ASSERT_EQ(*var1, std::vector<int>());

    ASSERT_FALSE(var1 < var2);
    ASSERT_FALSE(var1 > var2);
    ASSERT_TRUE(var1 <= var2);
    ASSERT_TRUE(var1 >= var2);

    ASSERT_TRUE(var1 == var2);
    ASSERT_FALSE(var1 != var2);

    ASSERT_EQ(var1 + var2, Variable());
    ASSERT_EQ(var1 - var2, Variable());
    ASSERT_EQ(var1 * var2, Variable({0}));
    ASSERT_EQ(var1 / var2, Variable());
    ASSERT_EQ(var1 % var2, Variable());
    ASSERT_EQ(var1.vectorProduct(var2), Variable());

    ASSERT_TRUE(var1 && var2);
    ASSERT_TRUE(var1 || var2);

    ASSERT_EQ(var1.toString(), "[]");
    ASSERT_EQ(var2.size(), 0);
}

TEST(ast_variable, variable_1d) {
    Variable var1 = Variable({0});
    Variable var2 = var1;

    ASSERT_EQ(*var1, std::vector<int>({0}));

    var1[0] = 5;
    ASSERT_EQ(*var1, std::vector<int>({5}));

    ASSERT_FALSE(var1 < var2);
    ASSERT_TRUE(var1 > var2);
    ASSERT_FALSE(var1 <= var2);
    ASSERT_TRUE(var1 >= var2);

    ASSERT_FALSE(var1 == var2);
    ASSERT_TRUE(var1 != var2);

    ASSERT_EQ(var1 + var2, Variable({5}));
    ASSERT_EQ(var1 - var2, Variable({5}));
    ASSERT_EQ(var1 * var2, Variable({0}));

    ASSERT_ANY_THROW(var1 / var2);
    ASSERT_ANY_THROW(var1 % var2);

    var2[0] = 5;
    ASSERT_EQ(var1 / var2, Variable({1}));
    ASSERT_EQ(var1 % var2, Variable({0}));

    ASSERT_EQ(var1.vectorProduct(var2), Variable());

    ASSERT_TRUE(var1 && var2);
    ASSERT_TRUE(var1 || var2);

    ASSERT_FALSE(Variable({0}) && Variable({0}));
    ASSERT_FALSE(Variable({0}) || Variable({0}));

    ASSERT_EQ(var1.toString(), "[5]");
    ASSERT_EQ(var2.size(), 1);
}

TEST(ast_variable, variable_2d) {
    Variable var1 = Variable({1, 2});
    Variable var2 = var1;

    ASSERT_EQ(*var1, std::vector<int>({1, 2}));

    var1[0] = 3;
    ASSERT_EQ(*var1, std::vector<int>({3, 2}));

    ASSERT_FALSE(var1 < var2);
    ASSERT_TRUE(var1 > var2);
    ASSERT_FALSE(var1 <= var2);
    ASSERT_TRUE(var1 >= var2);

    ASSERT_FALSE(var1 == var2);
    ASSERT_TRUE(var1 != var2);

    ASSERT_EQ(var1 + var2, Variable({4, 4}));
    ASSERT_EQ(var1 - var2, Variable({2, 0}));
    ASSERT_EQ(var1 * var2, Variable({7}));

    ASSERT_EQ(var1.vectorProduct(var2), Variable({0, -2}));

    ASSERT_TRUE(var1 && var2);
    ASSERT_TRUE(var1 || var2);

    ASSERT_EQ(var1.toString(), "[3, 2]");
    ASSERT_EQ(var2.size(), 2);
}

TEST(ast_variable, variable_3d) {
    Variable var1 = Variable({1, 2, 3});
    Variable var2 = var1;

    ASSERT_EQ(*var1, std::vector<int>({1, 2, 3}));

    var1[0] = 4;
    ASSERT_EQ(*var1, std::vector<int>({4, 2, 3}));

    ASSERT_FALSE(var1 < var2);
    ASSERT_TRUE(var1 > var2);
    ASSERT_FALSE(var1 <= var2);
    ASSERT_TRUE(var1 >= var2);

    ASSERT_FALSE(var1 == var2);
    ASSERT_TRUE(var1 != var2);

    ASSERT_EQ(var1 + var2, Variable({5, 4, 6}));
    ASSERT_EQ(var1 - var2, Variable({3, 0, 0}));
    ASSERT_EQ(var1 * var2, Variable({17}));

    ASSERT_EQ(var1.vectorProduct(var2), Variable({0, -9, 6}));

    ASSERT_TRUE(var1 && var2);
    ASSERT_TRUE(var1 || var2);

    ASSERT_EQ(var1.toString(), "[4, 2, 3]");
    ASSERT_EQ(var2.size(), 3);
}

TEST(ast_variable, bool_variable) {
    ASSERT_FALSE(Variable({0}));
    ASSERT_TRUE(Variable({1}));
    ASSERT_FALSE(Variable({1}) && Variable({0}));
    ASSERT_TRUE(Variable({1}) || Variable({0}));
}