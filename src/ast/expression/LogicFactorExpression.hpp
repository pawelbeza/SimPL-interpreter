#pragma once

#include "MathExpression.hpp"

namespace simpl {
    class LogicFactorExpression : public Expression {
    public:
        LogicFactorExpression() = delete;

        explicit LogicFactorExpression(std::shared_ptr<Expression> expression_, bool negation_ = false);

        Variable calculate() const override;
    private:
        bool negation;
        std::shared_ptr<Expression> expression;
    };
}