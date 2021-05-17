#pragma once

#include <memory>
#include <Expression.hpp>
#include <utility>
#include "Statement.hpp"

namespace simpl {
    class VariableAssignment : public Statement {
    public:
        VariableAssignment(std::shared_ptr<Variable> var_, std::shared_ptr<Expression> expr_);

        Return execute() override;
    private:
        std::shared_ptr<Variable> variable;
        std::shared_ptr<Expression> expr;
    };
}