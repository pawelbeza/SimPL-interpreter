#pragma once

#include "Block.hpp"

#include <string>
#include <utility>
#include <vector>
#include <memory>

namespace simpl {
    class Function {
    public:
        explicit Function(std::string id_, std::vector<std::string> &params_);
        explicit Function(std::string id_, std::vector<std::string> &params_, std::shared_ptr<Block> block_);

        Return execute(std::vector<Variable> args = std::vector<Variable>{});

        std::string getID() const;
        int getParametersNumber() const;
        std::shared_ptr<Block> getBlock() const;
    private:
        std::string id;
        std::vector<std::string> params;
        std::shared_ptr<Block> block;
    };
}



