#pragma once

#include "Function.hpp"

#include <string>
#include "unordered_map"

namespace simpl {
    class Program {
    public:
        Program() = default;

        void addFunction(std::shared_ptr<Function> &func);
        bool functionExists(const std::string& funcName) const;
        std::shared_ptr<Function> getFunction(std::string& funcName);

        Return execute() {
            if (functions.find("main") == functions.end())
                throw std::runtime_error("couldn't find main function");
            return functions.at("main")->execute();
        }
    private:
        std::unordered_map<std::string, std::shared_ptr<Function>> functions;
    };
}



