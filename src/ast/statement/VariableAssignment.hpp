#pragma once

namespace simpl {
    class VariableAssignment : public Statement {
    public:
        VariableAssignment(std::string varName_, std::shared_ptr<Expression> expr_) : varName(varName_), expr(expr_) {}
        Return execute() override{return Return();}
    private:
        std::string varName;
        std::shared_ptr<Expression> expr;
    };
}