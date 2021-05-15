#pragma once

#include "MathTermExpression.hpp"
#include "TokenType.h"

namespace simpl {
    class MathExpression : public Expression {
    public:
        MathExpression() = delete;

        explicit MathExpression(std::vector<std::shared_ptr<Expression>> expressions_, std::vector<TokenType> operatorTypes);

        Variable calculate() const override;
    private:
        std::vector<std::shared_ptr<Expression>> expressions;
        std::vector<TokenType> operatorTypes;
    };
}