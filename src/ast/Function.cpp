#include <iostream>
#include "Function.hpp"

using namespace simpl;

Function::Function(std::string id_, std::vector<std::string> &params_) : id(std::move(id_)), params(params_) {
    block = std::make_shared<Block>();
    for (const auto& param : params)
        block->addVariable(param);
}

Function::Function(std::string id_, std::vector<std::string> &params_, std::shared_ptr<Block> block_)
        : id(std::move(id_)), params(params_), block(std::move(block_)) {}

std::string Function::getID() const  {return id;}

int Function::getParametersNumber() const  {return params.size();}

std::shared_ptr<Block> Function::getBlock() const {return block;}

Return Function::execute(std::vector<Variable> args) {
    if (args.size() != params.size())
        throw std::runtime_error("arguments number doesn't match parameters number");

    std::vector<Variable> oldVars;
    for (const auto& param : params)
        oldVars.push_back(*block->getVariable(param));

    for (int i = 0; i < args.size(); i++)
        *(block->getVariable(params[i])) = args[i];

    Return ret = block->execute();

    for (int i = 0; i < params.size(); i++)
        *block->getVariable(params[i]) = oldVars[i];

    return ret;
}
