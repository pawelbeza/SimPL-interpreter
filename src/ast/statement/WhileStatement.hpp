#pragma once

#include "Statement.hpp"

namespace simpl {
    class WhileStatement : public Statement {
    public:
        WhileStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> block_) : expr(expr_), block(block_) {}
        Return execute() override{return Return();}
    private:
        std::shared_ptr<Expression> expr;
        std::shared_ptr<Block> block;
    };
}
