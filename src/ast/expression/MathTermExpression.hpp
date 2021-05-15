#pragma once

#include <utility>

#include "MathFactorExpression.hpp"
#include "TokenType.h"

namespace simpl {
    class MathTermExpression : public Expression {
    public:
        MathTermExpression() = delete;

        explicit MathTermExpression(std::vector<std::shared_ptr<Expression>> expressions_, std::vector<TokenType> factorTokenTypes);

        Variable calculate() const override;
    private:
        std::vector<std::shared_ptr<Expression>> expressions;
        std::vector<TokenType> operatorTypes;
    };
}