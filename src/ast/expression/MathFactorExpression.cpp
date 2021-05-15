#include "MathFactorExpression.hpp"

#include <utility>

using namespace simpl;

MathFactorExpression::MathFactorExpression(std::shared_ptr <Variable> variable_, bool minus_) : variable(std::move(variable_)), minus(minus_) {}

MathFactorExpression::MathFactorExpression(std::shared_ptr <Statement> functionCall_, bool minus_) :
functionCall(std::move(functionCall_)), minus(minus_) {}

MathFactorExpression::MathFactorExpression(std::shared_ptr <Expression> expression_, bool minus_) :
expression(std::move(expression_)), minus(minus_) {}

Variable MathFactorExpression::calculate() const {
    Variable res;
    if (variable) {
        res = *variable;
    } else if (functionCall) {
        auto funcCallReturn = functionCall->execute();
        if (funcCallReturn.type != Return::Type::Variable)
            throw std::runtime_error("function call doesn't return value");

        res = funcCallReturn.var;
    } else if(expression) {
        res = expression->calculate();
    }

    return minus ? -res : res;
}
