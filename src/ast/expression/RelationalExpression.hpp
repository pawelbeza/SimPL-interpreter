#pragma once

#include "LogicFactorExpression.hpp"

namespace simpl {
    class RelationalExpression : public Expression {
    public:
        explicit RelationalExpression(std::vector<std::shared_ptr<Expression>> expressions_) : expressions(expressions_) {

        }
    private:
        std::vector<std::shared_ptr<Expression>> expressions;
    };
}
