#pragma once

#include "Expression.hpp"

namespace simpl {
    class PrintStatement : public Statement {
        enum class PrintType {
            String,
            Expression
        };

    public:
        void addPrintArg(std::string arg) {
            printTypes.push_back(PrintType::String);
            stringArgs.push_back(arg);
             std::shared_ptr<Expression> exp;
        }

        void addPrintArg(std::shared_ptr<Expression> arg) {
            printTypes.push_back(PrintType::Expression);
            exprArgs.push_back(arg);
        }

        Return execute() override{return Return();}
    private:
        std::vector<PrintType> printTypes;
        std::vector<std::string> stringArgs;
        std::vector<std::shared_ptr<Expression>> exprArgs;
    };
}