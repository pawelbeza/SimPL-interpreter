#pragma once

#include "MathFactorExpression.hpp"

namespace simpl {
    class MathTermExpression : public Expression {
    public:
        explicit MathTermExpression(std::vector<std::shared_ptr<Expression>> expressions_) :
                expressions(expressions_) {};
    private:
        std::vector<std::shared_ptr<Expression>> expressions;
    };
}