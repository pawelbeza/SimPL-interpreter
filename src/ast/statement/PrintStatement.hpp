#pragma once

#include "Expression.hpp"
#include "Statement.hpp"

#include <memory>
#include <iostream>

namespace simpl {
    class PrintStatement : public Statement {
        enum class PrintType {
            String,
            Expression
        };

    public:
        explicit PrintStatement(std::ostream &ostream_ = std::cout);

        void addPrintArg(const std::string& arg);
        void addPrintArg(const std::shared_ptr<Expression>& arg);

        Return execute() override;
    private:
        std::vector<PrintType> printTypes;
        std::vector<std::string> stringArgs;
        std::vector<std::shared_ptr<Expression>> exprArgs;
        std::ostream &os;
    };
}