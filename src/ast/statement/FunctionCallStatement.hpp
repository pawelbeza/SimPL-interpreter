#pragma once

#include <Expression.hpp>
#include <memory>
#include <Function.hpp>
#include "Statement.hpp"

namespace simpl {
    class FunctionCallStatement : public Statement {
    public:
        FunctionCallStatement(std::shared_ptr<Function> func_, std::vector<std::shared_ptr<Expression>> args_);

        Return execute() override;

    private:
        std::shared_ptr<Function> func;
        std::vector<std::shared_ptr<Expression>> args;
    };
};