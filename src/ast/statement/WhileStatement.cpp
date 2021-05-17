#include "WhileStatement.hpp"

#include <utility>

using namespace simpl;

WhileStatement::WhileStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> block_)
        : expr(std::move(expr_)), block(std::move(block_)) {}

Return WhileStatement::execute() {
    while(expr->calculate())
        block->execute();
    return Return();
}
