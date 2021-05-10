#pragma once

#include "Function.hpp"

#include <string>
#include "unordered_map"

namespace simpl {
    class Program {
    public:
        void addFunction(std::shared_ptr<Function> &func) {
            std::string funcID = func.getID();
            functions.insert({funcID, func});
        };
    private:
        std::unordered_map<std::string, std::shared_ptr<Function>> functions;
    };
}



