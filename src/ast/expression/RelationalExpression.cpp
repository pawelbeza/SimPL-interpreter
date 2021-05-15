#include "RelationalExpression.hpp"

using namespace simpl;

RelationalExpression::RelationalExpression(std::vector<std::shared_ptr<Expression>> expressions_, std::vector<TokenType> relOps_) {
    if (expressions_.size() - 1 != relOps_.size())
        throw std::runtime_error("given: " + std::to_string(relOps_.size()) +" relational operators, expected: " +
                                 std::to_string(expressions_.size() - 1));

    expressions = std::move(expressions_);
    relOps = std::move(relOps_);
}

Variable RelationalExpression::calculate() const {
    if (expressions.empty())
        return Variable();

    Variable res = expressions[0]->calculate();
    for (int i = 0; i < relOps.size(); i++) {
        Variable nextVar = expressions[i + 1]->calculate();
        if (relOps[i] == TokenType::Equality)
            res = res == nextVar;
        else if (relOps[i] == TokenType::Inequality)
            res = res != nextVar;
        else if (relOps[i] == TokenType::Less)
            res = res < nextVar;
        else if (relOps[i] == TokenType::LessOrEqual)
            res = res <= nextVar;
        else if (relOps[i] == TokenType::Greater)
            res = res > nextVar;
        else if (relOps[i] == TokenType::GreaterOrEqual)
            res = res >= nextVar;
        else
            throw std::runtime_error("bad token type in relational expression");
    }

    return res;
}
