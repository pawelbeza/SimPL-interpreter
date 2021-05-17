#include "Block.hpp"

using namespace simpl;

Block::Block(std::shared_ptr<Block> parentBlock_) : parentBlock(std::move(parentBlock_)) {}

Block::Block(std::shared_ptr<Block> parentBlock_, std::vector<std::shared_ptr<Statement>> statements_,
             std::unordered_map<std::string, std::shared_ptr<Variable>> variables_) :
        parentBlock(std::move(parentBlock_)), statements(std::move(statements_)), variables(std::move(variables_)) {}

void Block::addStatement(const std::shared_ptr<Statement> &statement) {
    statements.push_back(statement);
}

void Block::addVariable(const std::string &varName) {
    variables.insert({varName, std::make_shared<Variable>()});
}

std::shared_ptr<Variable> Block::getVariable(const std::string &varName) {
    if (variables.find(varName) != variables.end())
        return variables.at(varName);
    if (parentBlock)
        return parentBlock->getVariable(varName);
    throw std::runtime_error("couldn't find variable \"" + varName + "\"");
}

bool Block::existsVariable(const std::string &varName) {
    return variables.find(varName) != variables.end() || (parentBlock ? parentBlock->existsVariable(varName) : false);
}

Return Block::execute() {
    for (auto statement : statements) {
        Return ret = statement->execute();
        if (ret.type != Return::Type::None)
            return ret;
    }

    return Return();
}
