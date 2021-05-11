#pragma once

#include "MathExpression.hpp"

namespace simpl {
    class LogicFactorExpression : public Expression {
    public:
        explicit LogicFactorExpression(std::shared_ptr<Expression> expression_, bool negation_ = false) :
                expression(expression_), negation(negation_) {};
    private:
        bool negation;
        std::shared_ptr<Expression> expression;
    };
}