#pragma once

#include <Expression.hpp>
#include "Statement.hpp"
#include "Block.hpp"

#include <memory>

namespace simpl {
    class IfStatement : public Statement {
    public:
        IfStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> ifBlock_);
        IfStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> ifBlock_, std::shared_ptr<Block> elseBlock_);

        Return execute() override;
    private:
        std::shared_ptr<Expression> expr;
        std::shared_ptr<Block> ifBlock;
        std::shared_ptr<Block> elseBlock;
    };
};