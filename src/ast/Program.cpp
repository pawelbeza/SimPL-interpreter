#include "Program.hpp"

using namespace simpl;

void Program::addFunction(std::shared_ptr<Function> &func) {
    std::string funcID = func->getID();
    functions.insert({funcID, func});
}

bool Program::functionExists(const std::string &funcName) const  {
    return functions.find(funcName) != functions.end();
}

std::shared_ptr<Function> Program::getFunction(std::string &funcName) {
    return functions.at(funcName);
}
