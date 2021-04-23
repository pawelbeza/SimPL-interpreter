#pragma once

#include "TokenType.h"
#include "TokenTypeFactory.h"

#include <string>
#include "unordered_map"

namespace simpl {
    class Token {
    public:
        explicit Token(const TokenType &type = TokenType::Eof, std::string value = "");

        TokenType getType() const { return type; }

        std::string getValue() const { return value; }

        std::string toString() { return TokenTypeFactory::getTokenTypeName(type) + " " + value; };
    private:
        TokenType type;
        std::string value;
    };
}
