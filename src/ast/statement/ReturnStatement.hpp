#pragma once

#include <Expression.hpp>
#include "Statement.hpp"

#include <memory>

namespace simpl {
    class ReturnStatement : public Statement {
    public:
        explicit ReturnStatement();
        explicit ReturnStatement(std::shared_ptr<Expression> expr_);

        Return execute() override;
    private:
        std::shared_ptr<Expression> expr;
        Return::Type returnType;
    };
}