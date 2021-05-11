#pragma once

#include "RelationalExpression.hpp"

namespace simpl {
    class AndExpression : public Expression {
    public:
        explicit AndExpression(std::vector<std::shared_ptr<Expression>> expressions_) :
                expressions(expressions_) {}

    private:
        std::vector<std::shared_ptr<Expression>> expressions;
    };
}