#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Token.h"
#include "TokenTypeFactory.h"

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
    std::cout << file.eof();
    std::cout << "Found following tokens in file:" << std::endl;
    try {
        lexer.readNextToken();
        while(lexer.getToken().getType() != simpl::TokenType::Eof) {
            simpl::Token token = lexer.getToken();
            std::string tokenTypeName = simpl::TokenTypeFactory::getTokenTypeName(token.getType());

            std::cout << "type: " << tokenTypeName << " value: " << token.getValue() << std::endl;

            lexer.readNextToken();
        }
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    file.close();
}