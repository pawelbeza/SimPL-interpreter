#pragma once

#include <Expression.hpp>
#include "Statement.hpp"
#include "Block.hpp"

#include <memory>

namespace simpl {
    class WhileStatement : public Statement {
    public:
        WhileStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> block_);

        Return execute() override;
    private:
        std::shared_ptr<Expression> expr;
        std::shared_ptr<Block> block;
    };
}
