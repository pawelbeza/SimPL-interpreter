#pragma once

#include <Statement.hpp>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "Variable.hpp"

namespace simpl {
    class Block : public Statement {
    public:
        Block() = default;

        explicit Block(std::shared_ptr<Block> parentBlock_) :parentBlock(std::move(parentBlock_)) {}

        Block(std::shared_ptr<Block> parentBlock_, std::vector<std::shared_ptr<Statement>> statements_, std::unordered_map<std::string, Variable> variables_) :
        parentBlock(std::move(parentBlock_)), statements(std::move(statements_)), variables(std::move(variables_)){}

        void addStatement(const std::shared_ptr<Statement>& statement) {
            statements.push_back(statement);
        }

        void addVariable(const std::string& varName) {
            variables.insert({varName, Variable()});
        }

        Variable &getVariable(const std::string& varName) {
            if (variables.find(varName) != variables.end())
                return variables.at(varName);
            if (parentBlock)
                return parentBlock->getVariable(varName);
            throw std::runtime_error("couldn't find variable \"" + varName + "\"");
        }

        bool existsVariable(const std::string& varName) {
            return variables.find(varName) != variables.end() || (parentBlock ? parentBlock->existsVariable(varName) : false);
        }

        Return execute() override{return Return();}
    private:
        std::shared_ptr<Block> parentBlock;
        std::vector<std::shared_ptr<Statement>>  statements;
        std::unordered_map<std::string, Variable> variables;
    };
};
