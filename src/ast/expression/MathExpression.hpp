#pragma once

#include "MathTermExpression.hpp"

namespace simpl {
    class MathExpression : public Expression {
    public:
        explicit MathExpression(std::vector<std::shared_ptr<Expression>> expressions_) : expressions(expressions_){}
    private:
        std::vector<std::shared_ptr<Expression>> expressions;
    };
}