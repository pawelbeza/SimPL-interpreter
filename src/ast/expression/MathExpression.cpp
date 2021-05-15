#include "MathExpression.hpp"

#include <utility>

using namespace simpl;

MathExpression::MathExpression(std::vector<std::shared_ptr<Expression>> expressions_, std::vector<TokenType> operatorTypes_) {
    if (expressions_.size() - 1 != operatorTypes_.size())
        throw std::runtime_error("given: " + std::to_string(operatorTypes_.size()) +" additive operators, expected: " +
                                 std::to_string(expressions_.size() - 1));

    expressions = std::move(expressions_);
    operatorTypes = std::move(operatorTypes_);
}

Variable MathExpression::calculate() const {
    if (expressions.empty())
        return Variable();

    Variable res = expressions[0]->calculate();
    for (int i = 0; i < operatorTypes.size(); i++) {
        Variable nextVar = expressions[i + 1]->calculate();
        if (operatorTypes[i] == TokenType::Plus)
            res = res + nextVar;
        else if(operatorTypes[i] == TokenType::Minus)
            res = res - nextVar;
        else
            throw std::runtime_error("bad token type in additive expression");
    }

    return res;
}
