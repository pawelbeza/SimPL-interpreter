#pragma once

namespace simpl {
    class ReturnStatement : public Statement {
    public:
        ReturnStatement(std::shared_ptr<Expression> expr_) : expr(expr_) {}
    private:
        std::shared_ptr<Expression> expr;
    };
}