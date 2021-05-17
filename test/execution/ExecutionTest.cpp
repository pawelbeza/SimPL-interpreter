#include <gtest/gtest.h>
#include <Lexer.h>
#include <Parser.hpp>
#include <utility>

using namespace simpl;

struct ExecutionTestParams {
    std::string input;
    bool expectThrow;
    bool expectRetValue;
    Variable expectedRetVar;
};

class ExecutionTest : public ::testing::TestWithParam<ExecutionTestParams> {
};

TEST_P(ExecutionTest, parsing) {
    ExecutionTestParams params = GetParam();

    std::istringstream in(params.input);
    Lexer lexer(in);
    Parser parser(lexer);

    std::string diagnosticMsg("Input: \"" + params.input + "\"");
    std::shared_ptr<Program> program;
    ASSERT_NO_THROW(program = parser.parse()) << diagnosticMsg;

    if (params.expectThrow) {
        ASSERT_THROW(program->execute(), std::runtime_error) << diagnosticMsg;
    } else {
        Return ret;
        ASSERT_NO_THROW(ret = program->execute()) << diagnosticMsg;

        if (params.expectRetValue) {
            ASSERT_EQ(ret.type, Return::Type::Variable);
            ASSERT_EQ(ret.var, params.expectedRetVar);
        } else {
            ASSERT_EQ(ret.type, Return::Type::None);
        }
    }
}

INSTANTIATE_TEST_CASE_P(empty_function_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func id() {}", true},
        ExecutionTestParams{"func main() {}", false, false}
));

INSTANTIATE_TEST_CASE_P(return_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {return 1;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return [1,2];}", false, true, Variable({1,2})},
        ExecutionTestParams{"func main() {return [1,2,3];}", false, true, Variable({1,2,3})}
));

INSTANTIATE_TEST_CASE_P(definition_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {a := 1; return a;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {a := [1, 2]; return a;}", false, true, Variable({1, 2})},
        ExecutionTestParams{"func main() {a := [1, 2, 3]; return a;}", false, true, Variable({1, 2, 3})}
));

INSTANTIATE_TEST_CASE_P(assignment_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {a := 1; a = 2; return a;}", false, true, Variable({2})},
        ExecutionTestParams{"func main() {a := [1, 1]; a = [2, 2]; return a;}", false, true, Variable({2, 2})},
        ExecutionTestParams{"func main() {a := [1, 1, 1]; a = [2, 2, 2]; return a;}", false, true, Variable({2, 2, 2})}
));

INSTANTIATE_TEST_CASE_P(math_expression_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {return 1 + 1;}", false, true, Variable({2})},
        ExecutionTestParams{"func main() {return 1 + 2 + 3;}", false, true, Variable({6})},
        ExecutionTestParams{"func main() {a := 1; return a + 1;}", false, true, Variable({2})},
        ExecutionTestParams{"func main() {return 1 - 1;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return -1 - 1;}", false, true, Variable({-2})},
        ExecutionTestParams{"func main() {return -1 - 1 + 1;}", false, true, Variable({-1})},
        ExecutionTestParams{"func main() {return 2 * 2;}", false, true, Variable({4})},
        ExecutionTestParams{"func main() {return -2 * 2;}", false, true, Variable({-4})},
        ExecutionTestParams{"func main() {return -2 * (-2);}", false, true, Variable({4})},
        ExecutionTestParams{"func main() {return 2 / 2;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 2 / (-2);}", false, true, Variable({-1})},
        ExecutionTestParams{"func main() {return 2 / 0;}", true},
        ExecutionTestParams{"func main() {return 2 % 2;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return 2/2 % 2;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 2/2 + 5 % 2;}", false, true, Variable({2})},
        ExecutionTestParams{"func main() {return (2/2 + 5) % 2;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return (2/2 + 5) % 2 - 1;}", false, true, Variable({-1})},
        ExecutionTestParams{"func main() {return (2/2 + 5) % 2 - 1 * 10;}", false, true, Variable({-10})},
        ExecutionTestParams{"func main() {return [1,2] + [3,2];}", false, true, Variable({4,4})},
        ExecutionTestParams{"func main() {return [1,2] - [3,2];}", false, true, Variable({-2,0})},
        ExecutionTestParams{"func main() {return [1,2] / [3,2];}", false, true, Variable({0,1})},
        ExecutionTestParams{"func main() {return [1,2] % [3,2];}", false, true, Variable({1, 0})},
        ExecutionTestParams{"func main() {return [1,2] * [3,2];}", false, true, Variable({7})},
        ExecutionTestParams{"func main() {return [1,2] x [3,2];}", false, true, Variable({1,2}).vectorProduct(Variable({3,2}))},
        ExecutionTestParams{"func main() {return [1,2,3] + [3,2,1];}", false, true, Variable({4,4,4})},
        ExecutionTestParams{"func main() {return [1,2,3] - [3,2,1];}", false, true, Variable({-2,0,2})},
        ExecutionTestParams{"func main() {return [1,2,3] / [3,2,1];}", false, true, Variable({0,1,3})},
        ExecutionTestParams{"func main() {return [1,2,3] % [3,2,1];}", false, true, Variable({1,0,0})},
        ExecutionTestParams{"func main() {return [1,2,3] * [3,2,1];}", false, true, Variable({10})},
        ExecutionTestParams{"func main() {return [1,2,3] x [3,2,1];}", false, true, Variable({1,2,3}).vectorProduct(Variable({3,2,1}))},
        ExecutionTestParams{"func main() {return [1,2,3] + [3,2];}", true},
        ExecutionTestParams{"func main() {return [2,3] - [3,2,1];}", true},
        ExecutionTestParams{"func main() {return [1,2] / [3,2,1];}", true},
        ExecutionTestParams{"func main() {return [1,2,3] % [3,1];}", true},
        ExecutionTestParams{"func main() {return [1,2,3] * [2,1];}", true},
        ExecutionTestParams{"func main() {return [1,2] x [3,2,1];}", true},
        ExecutionTestParams{"func main() {return [1,2] * [3,2] + [1,2,3] * [3,2,1];}", false, true, Variable({17})},
        ExecutionTestParams{"func main() {return [1,2] * [3,2] - 7 + [1,2,3] * [3,2,1];}", false, true, Variable({10})}
));

INSTANTIATE_TEST_CASE_P(logic_expression_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {return 1 == 1;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 1 != 1;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return (1+1) == 2;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 1 != 2;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 1 < 2;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 1 <= 2;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 1 > 2;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return 1 >= 2;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return 1 == 2 || 1 == 1;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 1 == 2 && 1 == 1;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return 2 == 2 && 1 == 1;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return 1 == 2 && 1 == 2;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return !(2 == 2 && 1 == 1);}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {return !(1 == 2 && 1 == 2);}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return [1, 1] != 1;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {return [1, 1, 1] != 1;}", false,  true, Variable({1})},
        ExecutionTestParams{"func main() {return [1, 1, 1] != [1,1 ];}", false,  true, Variable({1})}
));

INSTANTIATE_TEST_CASE_P(conditional_statement_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {if (1) { return 1; } return 0;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {if (0) { return 0; } return 1;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {if (1) { return 1; } else {return 0;}}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {if (0) { return 0; } else {return 1;}}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {if (0) { return 0; } if(1) {return 1;}}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {if (1) { if (1) { return 1; } else {return 0;} } }", false, true, Variable({1})},
        ExecutionTestParams{"func main() {if (1) { if (0) { return 0; } else {return 1;} } }", false, true, Variable({1})}
));

INSTANTIATE_TEST_CASE_P(while_statement_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {i := 0; while (i < 0) { i = i + 1;} return i;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {i := 0; while (i == 0) { i = i + 1;} return i;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {i := 0; while (i < 5) { i = i + 1;} return i;}", false, true, Variable({5})}
));

INSTANTIATE_TEST_CASE_P(block_statement_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func main() {i := 0; {i = 1;} return i;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {i := 0; return i; {i = 1;} return i;}", false, true, Variable({0})},
        ExecutionTestParams{"func main() {i := 0; {i = 1; {i = 2;}} return i;}", false, true, Variable({2})},
        ExecutionTestParams{"func main() {i := 0; {i = 1; return i; {i = 2;}} return i;}", false, true, Variable({1})},
        ExecutionTestParams{"func main() {i := 0; {i = 1; {i = 2;} {i = 3;}} return i;}", false, true, Variable({3})},
        ExecutionTestParams{"func main() {i := 0; {i = 1; {i = 2; return i;} {i = 3;}} return i;}", false, true, Variable({2})},
        ExecutionTestParams{"func main() {{i := 0; {i = 1; {i = 2;} {i = 3;}} i = 4; return i;}}", false, true, Variable({4})},
        ExecutionTestParams{"func main() {{i := 0; {i = 1; {i = 2;} {i = 3; return i;}} i = 4; return i;}}", false, true, Variable({3})}
));

INSTANTIATE_TEST_CASE_P(func_call_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func f() {return 1;}"
                            "func main() {return f();}", false, true, Variable({1})},
        ExecutionTestParams{"func f() {return 1;}"
                            "func main() {a := f(); return a;}", false, true, Variable({1})},
        ExecutionTestParams{"func f(a) {return a;}"
                            "func main() {a := f(1); return a;}", false, true, Variable({1})},
        ExecutionTestParams{"func f(a) {return a;}"
                            "func main() {a := 1; return f(a);}", false, true, Variable({1})},
        ExecutionTestParams{"func f(a) {a = 5;}"
                            "func main() {a := 1; f(a); return a;}", false, true, Variable({1})},
        ExecutionTestParams{"func f(a, b) {return a + b;}"
                            "func main() {return f(4, 5);}", false, true, Variable({9})},
        ExecutionTestParams{"func f(a) {a = 5;}"
                            "func main() {a := 1; f(a); return f(a);}", true}
));

INSTANTIATE_TEST_CASE_P(recursion_execution, ExecutionTest, ::testing::Values(
        ExecutionTestParams{"func f(a) {if (a == 0 || a == 1) {return 1;} return a * f(a - 1);}"
                            "func main() {return f(0);}", false, true, Variable({1})},
        ExecutionTestParams{"func f(a) {if (a == 0 || a == 1) {return 1;} return a * f(a - 1);}"
                            "func main() {return f(1);}", false, true, Variable({1})},
        ExecutionTestParams{"func f(a) {if (a == 0 || a == 1) {return 1;} return a * f(a - 1);}"
                            "func main() {return f(5);}", false, true, Variable({120})},
        ExecutionTestParams{"func fibb(a) {if (a == 0) {return 0;} if (a == 1) {return 1;} return fibb(a - 1) + fibb(a - 2);}"
                            "func main() {return fibb(0);}", false, true, Variable({0})},
        ExecutionTestParams{"func fibb(a) {if (a == 0) {return 0;} if (a == 1) {return 1;} return fibb(a - 1) + fibb(a - 2);}"
                            "func main() {return fibb(1);}", false, true, Variable({1})},
        ExecutionTestParams{"func fibb(a) {if (a == 0) {return 0;} if (a == 1) {return 1;} return fibb(a - 1) + fibb(a - 2);}"
                            "func main() {return fibb(2);}", false, true, Variable({1})},
        ExecutionTestParams{"func fibb(a) {if (a == 0) {return 0;} if (a == 1) {return 1;} return fibb(a - 1) + fibb(a - 2);}"
                            "func main() {return fibb(10);}", false, true, Variable({55})}
));
