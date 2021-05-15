#include "LogicExpression.hpp"

#include <utility>

using namespace simpl;

LogicExpression::LogicExpression(std::vector<std::shared_ptr<Expression>> expressions_) : expressions(std::move(expressions_)) {}

Variable LogicExpression::calculate() const {
    if (expressions.empty())
        return Variable();

    Variable res = expressions[0]->calculate();
    for (int i = 1; i < expressions.size(); i++) {
        Variable nextVar = expressions[i]->calculate();
        res = res || nextVar;
    }

    return res;
}
