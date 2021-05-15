#include <TokenType.h>

#include <utility>
#include "MathTermExpression.hpp"

using namespace simpl;

MathTermExpression::MathTermExpression(std::vector<std::shared_ptr<Expression>> expressions_, std::vector<TokenType> factorTokenTypes_) {
    if (expressions_.size() - 1 != factorTokenTypes_.size())
        throw std::runtime_error("given: " + std::to_string(factorTokenTypes_.size()) +" multiplicative operators, expected: " +
        std::to_string(expressions_.size() - 1));

    expressions = std::move(expressions_);
    operatorTypes = std::move(factorTokenTypes_);
}

Variable MathTermExpression::calculate() const {
    if (expressions.empty())
        return Variable();

    Variable res = expressions[0]->calculate();
    for (int i = 0; i < operatorTypes.size(); i++) {
        Variable nextVar = expressions[i + 1]->calculate();
        if (operatorTypes[i] == TokenType::ScalarMultiply)
            res = res * nextVar;
        else if(operatorTypes[i] == TokenType::VectorMultiply)
            res = res.vectorProduct(nextVar);
        else if (operatorTypes[i] == TokenType::Divide)
            res = res / nextVar;
        else if (operatorTypes[i] == TokenType::Modulo)
            res = res % nextVar;
        else
            throw std::runtime_error("bad token type in multiplicative expression");
    }

    return res;
}
