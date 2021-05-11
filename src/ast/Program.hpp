#pragma once

#include "Function.hpp"

#include <string>
#include "unordered_map"

namespace simpl {
    class Program {
    public:
        Program() = default;

        void addFunction(std::shared_ptr<Function> &func) {
            std::string funcID = func->getID();
            functions.insert({funcID, func});
        };

        bool functionExists(const std::string& funcName) const {
            return functions.find(funcName) != functions.end();
        }

        std::shared_ptr<Function> getFunction(std::string& funcName) {
            return functions.at(funcName);
        }
    private:
        std::unordered_map<std::string, std::shared_ptr<Function>> functions;
    };
}



