#pragma once

#include "TokenType.h"

#include <string>
#include <unordered_map>

namespace simpl {
    class TokenTypeFactory {
    public:
        static TokenType createTokenType(const std::string &lexeme);

        static std::string getTokenTypeName(const TokenType &typeName);

        static bool isTokenValid(const std::string &lexeme);

        static std::unordered_map<std::string, TokenType> getTokenTypes();
    };

    inline std::ostream &operator<<(std::ostream &o, TokenType type) {
        return o << TokenTypeFactory::getTokenTypeName(type);
    }
}
