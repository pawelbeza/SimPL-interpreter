#pragma once

#include "RelationalExpression.hpp"

namespace simpl {
    class AndExpression : public Expression {
    public:
        AndExpression() = delete;

        explicit AndExpression(std::vector<std::shared_ptr<Expression>> expressions_);

        Variable calculate() const override;

    private:
        std::vector<std::shared_ptr<Expression>> expressions;
    };
}