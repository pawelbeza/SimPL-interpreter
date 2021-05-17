#pragma once

#include <Statement.hpp>
#include "Variable.hpp"

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

namespace simpl {
    class Block : public Statement {
    public:
        Block() = default;

        explicit Block(std::shared_ptr<Block> parentBlock_);
        Block(std::shared_ptr<Block> parentBlock_, std::vector<std::shared_ptr<Statement>> statements_,
                     std::unordered_map<std::string, std::shared_ptr<Variable>> variables_);

        void addStatement(const std::shared_ptr<Statement>& statement);
        void addVariable(const std::string& varName);

        std::shared_ptr<Variable> getVariable(const std::string& varName);
        bool existsVariable(const std::string& varName);

        Return execute() override;
    private:
        std::shared_ptr<Block> parentBlock;
        std::vector<std::shared_ptr<Statement>>  statements;
        std::unordered_map<std::string, std::shared_ptr<Variable>> variables;
    };
};
