#pragma once

#include "AndExpression.hpp"

namespace simpl {
    class LogicExpression : public Expression {
    public:
        explicit LogicExpression(std::vector<std::shared_ptr<Expression>>  expressions_);

        Variable calculate() const override;
    private:
        std::vector<std::shared_ptr<Expression>>  expressions;
    };
}