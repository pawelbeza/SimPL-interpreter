#include "LogicFactorExpression.hpp"

#include <utility>

using namespace simpl;

LogicFactorExpression::LogicFactorExpression(std::shared_ptr<Expression> expression_, bool negation_)
: expression(std::move(expression_)), negation(negation_) {}

Variable LogicFactorExpression::calculate() const {
    Variable res = expression->calculate();
    return negation ? !res : res;
}


