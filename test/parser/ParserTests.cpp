#include "Parser.hpp"
#include "Lexer.h"

#include <gtest/gtest.h>

using namespace simpl;

struct ParserTestParams {
    std::string input;
    bool expectThrow;
};

class ParserTest : public ::testing::TestWithParam<ParserTestParams> {
};

TEST_P(ParserTest, parsing) {
    ParserTestParams params = GetParam();
    std::istringstream in(params.input);
    Lexer lexer(in);
    Parser parser(lexer);

    std::string diagnosticMsg("Input: \"" + params.input + "\"");
    if (params.expectThrow)
        EXPECT_THROW(parser.parse(), std::runtime_error) << diagnosticMsg;
    else
        EXPECT_NO_THROW(parser.parse()) << diagnosticMsg;
}

INSTANTIATE_TEST_CASE_P(FunctionParsing, ParserTest, ::testing::Values(
        ParserTestParams{"funcfoo", true},
        ParserTestParams{"func foo", true},
        ParserTestParams{"func foo(", true},
        ParserTestParams{"func foo(var", true},
        ParserTestParams{"func foo(var)", true},
        ParserTestParams{"func foo(var);", true},
        ParserTestParams{"func foo(var, 1){}", true},
        ParserTestParams{"func foo(var){};", true},
        ParserTestParams{"func foo2(var1, ){}", true},
        ParserTestParams{"func foo(var){}", false},
        ParserTestParams{"func foo2(var1, var2){}", false},
        ParserTestParams{"func foo1(var){}"
                         "func foo2(var1, var2){}", false}
));

INSTANTIATE_TEST_CASE_P(VariableDefinition, ParserTest, ::testing::Values(
        ParserTestParams{"func foo() {"
                         "a : 1"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a :== 1"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 1"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a, b := 1, 2"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "b := 2;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "b := a;"
                         "}", false}
));

INSTANTIATE_TEST_CASE_P(VariableAssignment, ParserTest, ::testing::Values(
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "a = "
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "a := 2"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "a = 2"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "a = 2 * b"
                         "}", true},
        ParserTestParams{"func f() {{var = 1;}}", true},
        ParserTestParams{"func f() {var := 1; {var = 1;}}", false},
        ParserTestParams{"func f(var) {{var = 1;}}", false},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "a = 2;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := 1;"
                         "b := 2;"
                         "a = b;}", false},
        ParserTestParams{"func foo1() {return 3;}"
                         "func foo2() {"
                         "a := foo1();"
                         "}", false}
));

INSTANTIATE_TEST_CASE_P(MathExpression, ParserTest, ::testing::Values(
        ParserTestParams{"func foo() {"
                         "a := 1 +;"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 5 - 3 * (;"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 5 - ();"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 5 - 3 * (4 + 5 / 2;"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 5 - 3 * (4 + 5 / 2)"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := 5 + 3 /"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := [0];"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := [0,];"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := [0,1;"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := [0,1,];"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := [0,1,2,];"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := [0,1,2,3];"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "a := (1);"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := (1 * 2);"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := (1 * 2) % 2;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := - 5 * 6/3;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := (1 * 2) % 2 - 5 * 6/3 + 22;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := (2 + 5%2 - 5/2) * (2 - (5 * 44 - 5%2));"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := (2 - 2*(2 *5 - 10) * (5 - 2) + 5 - 5%2) * (41 - 5) + 11;"
                         "}", false},
        ParserTestParams{"func foo1(var) { return 5 * var;}"
                         "func foo2() {"
                         "var1 := 1;"
                         "var2 := 2;"
                         "a := var1 + var2 * foo1(var1);"
                         "}", false},
        ParserTestParams{"func foo1() { return 5;}"
                         "func foo2() {"
                         "var := 1;"
                         "a := (5 * var) % 2 - foo1() * 6/3 + 22;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := [0,1];"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := [0,1,2];"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := 1 + 2;"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := [0,1];"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := [0,1] * [1, 2];"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := [0,1] + [1, 2];"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := [0, 1, 2] * [1, 2, 3];"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "a := [0, 1, 2] + [1, 2, 3];"
                         "}", false}
));

INSTANTIATE_TEST_CASE_P(LogicExpression, ParserTest, ::testing::Values(
        ParserTestParams{"func foo() {"
                         "if (1 == ) {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "if (1 == (2 == 5 || ) {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "if (1 == 2;) {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "y := 5;"
                         "if (y-- > 4) {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "y := 5;"
                         "if (!!(y == 4)) {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "if (1 + 1 == 2) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if (1 + 1 - 5 == 2) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if ((2 * 3) - 5 == 1) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "y := 5;"
                         "if (!(y == 4)) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "y := 5;"
                         "if (!(!(y == 4))) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if ((2 * 3) - 5 / 2 != 10) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if (1==1 && 3 != 2) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if (1==1 || 3 != 2) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if ((1==1 || 3 != 2) && 5 == 5) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if ((1==1 || 3 >= 2) && 5 == 5) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "if (4 > 2 || 5 == 4 && 3 >= 4 || (4 <= 10 && 5 < 10 || 4 != 5)) {}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "y := 2;"
                         "if (y > 1) {}"
                         "}", false}
));

INSTANTIATE_TEST_CASE_P(ConditionalTest, ParserTest, ::testing::Values(
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "if (;) {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "if i == 1 {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "if (i == 1 {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "if (i == 1) {;}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "else {}"
                         "}", true},
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "if (i == 1) {;}"
                         "} else {}", true},
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "if (y == 1) {"
                         "y = 2;"
                         "}"
                         "}", false},
        ParserTestParams{"func foo() {"
                         "y := 1;"
                         "if (y == 1) {"
                         "y = 2;"
                         "} else {"
                         "y = 3;"
                         "}"
                         "}", false}
));

INSTANTIATE_TEST_CASE_P(PrintTest, ParserTest, ::testing::Values(
        ParserTestParams{"func f() {print;}", true},
        ParserTestParams{"func f() {print();}", true},
        ParserTestParams{"func f() {print(hello)}", true},
        ParserTestParams{"func f() {print(\"hello\")}", true},
        ParserTestParams{"func f() {print(\"hello\", );}", true},
        ParserTestParams{"func f() {print(\"hello\");}", false},
        ParserTestParams{"func f() {print(\"hello\n\");}", false},
        ParserTestParams{"func f() {print(\"\thello\n\");}", false},
        ParserTestParams{"func f() {print(\"\thello\n `world`\");}", false},
        ParserTestParams{"func f() {var := 1; print(\"\thello\n `world`\", 1, 5/2 + 4%var);}", false}
));

INSTANTIATE_TEST_CASE_P(WhileTest, ParserTest, ::testing::Values(
        ParserTestParams{"func f() {while}", true},
        ParserTestParams{"func f() {while(); {}}", true},
        ParserTestParams{"func f() {i := 1; while i == 1; {}}", true},
        ParserTestParams{"func f() {i := 1; while (i == 1 {i = i + 1}}", true},
        ParserTestParams{"func f() {i := 1; while (i == 1); {i = i + 1}}", true},
        ParserTestParams{"func f() {while(1 == 1) {}}", false},
        ParserTestParams{"func f() {i := 1; while (i == 1) {i = i + 1;}}", false}
));

INSTANTIATE_TEST_CASE_P(ReturnTest, ParserTest, ::testing::Values(
        ParserTestParams{"func f() {return}", true},
        ParserTestParams{"func f() {return;}", true},
        ParserTestParams{"func f() {return 3}", true},
        ParserTestParams{"func f() {return 3;}", false}
));

INSTANTIATE_TEST_CASE_P(FunctionCallTest, ParserTest, ::testing::Values(
        ParserTestParams{"func main() {a := fNotExists(); return a;}", true},
        ParserTestParams{"func f1() {return 2;}"
                         "func main() {a := f1() return a;}", true},
        ParserTestParams{"func f1(a) {return 2;}"
                         "func main() {a := f1(a,); return a;}", true},
        ParserTestParams{"func f1(a) {return 2;}"
                         "func main() {a := f1(a, b); return a;}", true},
        ParserTestParams{"func f1() {return 2;}"
                         "func main() {a := f1(; return a;}", true},
        ParserTestParams{"func f() {return 2;}"
                         "func main() {a := f(); return a;}", false},
        ParserTestParams{"func f(a) {return 2 * a;}"
                         "func main() {a := f(2); return a;}", false}
));

INSTANTIATE_TEST_CASE_P(BlockTest, ParserTest, ::testing::Values(
        ParserTestParams{"func f() {} {}", true},
        ParserTestParams{"func f() { {}", true},
        ParserTestParams{"func f() { {i : = 1} i = i + 1;}", true},
        ParserTestParams{"func f() { {i : = 1} {i = i + 1;}}", true},
        ParserTestParams{"func f() {{}}", false},
        ParserTestParams{"func f() {{} {}}", false},
        ParserTestParams{"func f() {{{{}} {}}}", false},
        ParserTestParams{"func f(a) { {a = 1;} }", false},
        ParserTestParams{"func f() { i := 0; {i = 1;}}", false},
        ParserTestParams{"func f() { i := 0; {i = 2; {i = 1;}}}", false},
        ParserTestParams{"func slow_pow(base, exp) {"
                         "result := 1;"
                         "while (exp > 0) {"
                         "result = result * base;"
                         "exp = exp - 1;"
                         "}"
                         "return result;"
                         "}", false},
        ParserTestParams{"func ugly_factorial(n) {"
                         "    if (n <= 1) {"
                         "        return 1;"
                         "    }"
                         "print(\":)\n\");"
                         "    return ugly_factorial(n - 1) * n;\n"
                         "}", false}
));