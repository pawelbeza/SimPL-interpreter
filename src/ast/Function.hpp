#pragma once

#include "Block.hpp"

#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace simpl {
    class Function {
    public:
        explicit Function(std::string id_, std::vector<std::string> &params_): id(std::move(id_)), params(params_) {
            block = std::make_shared<Block>();
            for (const auto& param : params)
                block->addVariable(param);
        }

        explicit Function(std::string id_, std::vector<std::string> &params_, std::shared_ptr<Block> block_)
        : id(std::move(id_)), params(params_), block(std::move(block_)) {}

        std::string getID() const {return id;}
        int getParametersNumber() const {return params.size();}
        std::shared_ptr<Block> getBlock() const {return block;}
    private:
        std::string id;
        std::vector<std::string> params;
        std::shared_ptr<Block> block;
    };
}



