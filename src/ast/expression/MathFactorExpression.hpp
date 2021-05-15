#pragma once

#include <Variable.hpp>
#include "Expression.hpp"
#include <Statement.hpp>

#include <utility>
#include <vector>
#include <memory>

namespace simpl {
    class MathFactorExpression : public Expression {
    public:
        MathFactorExpression() = delete;

        explicit MathFactorExpression(std::shared_ptr <Variable> var, bool minus_ = false);
        explicit MathFactorExpression(std::shared_ptr <Statement> functionCall_, bool minus_ = false);
        explicit MathFactorExpression(std::shared_ptr <Expression> expression_, bool minus_ = false);

        Variable calculate() const override;

    private:
        bool minus;
        std::shared_ptr <Variable> variable;
        std::shared_ptr <Statement> functionCall;
        std::shared_ptr <Expression> expression;
    };
}