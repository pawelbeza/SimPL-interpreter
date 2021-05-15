#pragma once

namespace simpl {
    class ReturnStatement : public Statement {
    public:
        ReturnStatement(std::shared_ptr<Expression> expr_) : expr(expr_) {}
        Return execute() override{return Return();}
    private:
        std::shared_ptr<Expression> expr;
    };
}