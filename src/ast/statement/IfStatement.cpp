#include "IfStatement.hpp"

#include <utility>

using namespace simpl;

IfStatement::IfStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> ifBlock_)
        : expr(std::move(expr_)), ifBlock(std::move(ifBlock_)) {}

IfStatement::IfStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> ifBlock_, std::shared_ptr<Block> elseBlock_)
        : expr(std::move(expr_)), ifBlock(std::move(ifBlock_)), elseBlock(std::move(elseBlock_)) {}

Return IfStatement::execute() {
    if(expr->calculate())
        return ifBlock->execute();
    else if (elseBlock)
        return elseBlock->execute();
    else
        return Return();
}
