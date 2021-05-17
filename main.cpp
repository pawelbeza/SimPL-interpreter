#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Return.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "need file path as argument";
        return 0;
    }

    std::fstream file;

    file.open(argv[1], std::ios::in);
    if (!file.good()) {
        std::cout << "file not found";
        return -1;
    }

    simpl::Lexer lexer(file);
    try {
        simpl::Parser parser(lexer);
        auto program = parser.parse();

        simpl::Return ret = program->execute();
        if (ret.type == simpl::Return::Type::Variable)
            std::cout << ret.var;
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    file.close();
}