#include "FunctionCallStatement.hpp"

#include <utility>

using namespace simpl;

FunctionCallStatement::FunctionCallStatement(std::shared_ptr<Function> func_, std::vector<std::shared_ptr<Expression>> args_)
        : func(std::move(func_)), args(std::move(args_)) {}

Return FunctionCallStatement::execute() {
    std::vector<Variable> calculatedArgs;
    for (auto arg : args)
        calculatedArgs.push_back(arg->calculate());

    return func->execute(calculatedArgs);
}
