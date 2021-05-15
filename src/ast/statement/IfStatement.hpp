#pragma once

namespace simpl {
    class IfStatement : public Statement {
    public:
        IfStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> ifBlock_)
                : expr(expr_), ifBlock(ifBlock_) {}

        IfStatement(std::shared_ptr<Expression> expr_, std::shared_ptr<Block> ifBlock_, std::shared_ptr<Block> elseBlock_)
        : expr(expr_), ifBlock(ifBlock_), elseBlock(elseBlock_) {}

        Return execute() override{return Return();}
    private:
        std::shared_ptr<Expression> expr;
        std::shared_ptr<Block> ifBlock;
        std::shared_ptr<Block> elseBlock;
    };
};