#include "TokenTypeFactory.h"

using namespace simpl;

TokenType TokenTypeFactory::createTokenType(const std::string &lexeme) {
    auto tokens = getTokenTypes();
    auto tokenIter = tokens.find(lexeme);
    return tokenIter != tokens.end() ? tokenIter->second : TokenType::Eof;
}

bool TokenTypeFactory::isTokenValid(const std::string &lexeme) {
    auto tokens = getTokenTypes();
    return tokens.find(lexeme) != tokens.end();
}

std::string TokenTypeFactory::getTokenTypeName(const TokenType &typeName) {
    const static std::unordered_map<TokenType, std::string> typeNames{
            {TokenType::Function,           "Function"},
            {TokenType::While,              "While"},
            {TokenType::Return,             "Return"},
            {TokenType::If,                 "If"},
            {TokenType::Else,               "Else"},
            {TokenType::Print,              "Print"},

            {TokenType::Plus,               "Plus"},
            {TokenType::Minus,              "Minus"},
            {TokenType::ScalarMultiply,     "ScalarMultiply"},
            {TokenType::VectorMultiply,     "VectorMultiply"},
            {TokenType::Divide,             "Divide"},
            {TokenType::Modulo,             "Modulo"},
            {TokenType::Equality,           "Equality"},
            {TokenType::Inequality,         "Inequality"},
            {TokenType::Less,               "Less"},
            {TokenType::LessOrEqual,        "LessOrEqual"},
            {TokenType::Greater,            "Greater"},
            {TokenType::GreaterOrEqual,     "GreaterOrEqual"},
            {TokenType::Negation,           "Negation"},
            {TokenType::And,                "And"},
            {TokenType::Or,                 "Or"},

            {TokenType::RoundBracketOpen,   "RoundBracketOpen"},
            {TokenType::RoundBracketClose,  "RoundBracketClose"},
            {TokenType::CurlyBracketOpen,   "CurlyBracketOpen"},
            {TokenType::CurlyBracketClose,  "CurlyBracketClose"},
            {TokenType::SquareBracketOpen,  "SquareBracketOpen"},
            {TokenType::SquareBracketClose, "SquareBracketClose"},
            {TokenType::Comma,              "Comma"},
            {TokenType::Semicolon,          "Semicolon"},
            {TokenType::Definition,         "Definition"},
            {TokenType::Assignment,         "Assignment"},

            {TokenType::Id,                 "Id"},
            {TokenType::String,             "String"},
            {TokenType::Int,                "Int"},

            {TokenType::Eof,                "Eof"},
    };
    return typeNames.at(typeName);
}

std::unordered_map<std::string, TokenType> TokenTypeFactory::getTokenTypes() {
    const static std::unordered_map<std::string, TokenType> types{
            {"func",   TokenType::Function},
            {"while",  TokenType::While},
            {"return", TokenType::Return},
            {"if",     TokenType::If},
            {"else",   TokenType::Else},
            {"print",  TokenType::Print},

            {"+",      TokenType::Plus,},
            {"-",      TokenType::Minus},
            {"*",      TokenType::ScalarMultiply},
            {"x",      TokenType::VectorMultiply},
            {"/",      TokenType::Divide},
            {"%",      TokenType::Modulo},
            {"==",     TokenType::Equality},
            {"!=",     TokenType::Inequality},
            {"<",      TokenType::Less},
            {"<=",     TokenType::LessOrEqual},
            {">",      TokenType::Greater},
            {">=",     TokenType::GreaterOrEqual},
            {"!",      TokenType::Negation},
            {"&&",     TokenType::And},
            {"||",     TokenType::Or},

            {"(",      TokenType::RoundBracketOpen},
            {")",      TokenType::RoundBracketClose},
            {"{",      TokenType::CurlyBracketOpen},
            {"}",      TokenType::CurlyBracketClose},
            {"[",      TokenType::SquareBracketOpen},
            {"]",      TokenType::SquareBracketClose},
            {",",      TokenType::Comma},
            {";",      TokenType::Semicolon},
            {":=",     TokenType::Definition},
            {"=",      TokenType::Assignment},
    };
    return types;
}
