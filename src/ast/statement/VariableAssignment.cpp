#include "VariableAssignment.hpp"

#include <utility>

using namespace simpl;

VariableAssignment::VariableAssignment(std::shared_ptr<Variable> var_, std::shared_ptr<Expression> expr_)
: variable(std::move(var_)), expr(std::move(expr_)) {}

Return VariableAssignment::execute() {
    *variable = expr->calculate();
    return Return();
}
