#pragma once

#include <istream>
#include "Token.h"

namespace simpl {
    class Lexer {
    public:
        explicit Lexer(std::istream &in);

        void readNextToken();

        Token getToken() { return token; };

    private:
        bool tryEof();
        bool tryIdOrKeyword();
        bool tryNumber();
        bool tryString();
        bool tryOperator();

        void ignoreWhitespaces();

        std::istream &in;
        Token token;
    };
}