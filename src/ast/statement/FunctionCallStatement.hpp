#pragma once

#include <Expression.hpp>

namespace simpl {
    class FunctionCallStatement : public Statement {
    public:
        FunctionCallStatement(std::shared_ptr<Function> func_, std::vector<std::shared_ptr<Expression>> args_) :
        func(func_), args(args_) {}
    private:
        std::shared_ptr<Function> func;
        std::vector<std::shared_ptr<Expression>> args;
    };
};