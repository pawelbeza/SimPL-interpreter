#include "PrintStatement.hpp"

#include <sstream>
#include <iostream>

using namespace simpl;

PrintStatement::PrintStatement(std::ostream &ostream_) : os(ostream_) {
}

void PrintStatement::addPrintArg(const std::string &arg) {
    printTypes.push_back(PrintType::String);
    stringArgs.push_back(arg);
    std::shared_ptr<Expression> exp;
}

void PrintStatement::addPrintArg(const std::shared_ptr<Expression> &arg) {
    printTypes.push_back(PrintType::Expression);
    exprArgs.push_back(arg);
}

Return PrintStatement::execute() {
    int j, k;
    j = k = 0;

    for (auto &printType : printTypes) {
        if (printType == PrintType::String) {
            os << stringArgs[j];
            j++;
        } else {
            auto expr = exprArgs[k]->calculate();
            os << expr;
            k++;
        }
    }

    return Return();
}
