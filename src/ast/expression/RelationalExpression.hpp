#pragma once

#include "LogicFactorExpression.hpp"

namespace simpl {
    class RelationalExpression : public Expression {
    public:
        RelationalExpression() = delete;

        explicit RelationalExpression(std::vector<std::shared_ptr<Expression>> expressions_, std::vector<TokenType> relOps_);

        Variable calculate() const override;
    private:
        std::vector<std::shared_ptr<Expression>> expressions;
        std::vector<TokenType> relOps;
    };
}
