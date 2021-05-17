#include "Lexer.h"
#include "Token.h"
#include "TokenTypeFactory.h"

#include <stdexcept>

using namespace simpl;

Lexer::Lexer(std::istream &in_) : in(in_) {
    token = Token();
}

void Lexer::readNextToken() {
    ignoreWhitespaces();
    if (tryEof()) {
        return;
    }

    if (tryIdOrKeyword() || tryNumber() || tryString() || tryOperator()) {
        return;
    }

    throw std::runtime_error(token.toString());
}

void Lexer::ignoreWhitespaces() {
    while (in && std::isspace(in.peek()))
        in.get();
}

bool Lexer::tryEof() {
    if (!in.eof())
        return false;

    token = Token();
    return true;
}

bool Lexer::tryIdOrKeyword() {
    if (!std::isalpha(in.peek())) {
        return false;
    }

    std::string buf;
    while (std::isalnum(in.peek()) || in.peek() == '_')
        buf += static_cast<char>(in.get());

    TokenType type = (TokenTypeFactory::isTokenValid(buf)) ? TokenTypeFactory::createTokenType(buf) : TokenType::Id;
    token = Token(type, buf);

    return true;
}

bool Lexer::tryNumber() {
    if (!std::isdigit(in.peek())) {
        return false;
    }

    std::string buf;
    while (std::isdigit(in.peek()))
        buf += static_cast<char>(in.get());

    token = Token(TokenType::Int, buf);
    return true;
}

bool Lexer::tryString() {
    if (in.peek() != '"')
        return false;

    in.get();

    std::string buf;
    while ((std::isprint(in.peek()) || std::isspace(in.peek())) && in.peek() != '"') {
        if (in.peek() == '\\') {
            in.get();
            if (in.peek() == '"') {
                buf += static_cast<char>(in.get());
            } else if (in.peek() == 'n') {
                buf += '\n';
                in.get();
            } else {
                buf += '\\';
                in.get();
            }
        } else {
            buf += static_cast<char>(in.get());
        }
    }

    if (in.peek() != '"') {
        return false;
    }

    in.get();
    token = Token(TokenType::String, buf);

    return true;
}

bool Lexer::tryOperator() {
    std::string buf;
    buf += static_cast<char>(in.get());

    char nextChar = in.peek();
    if (TokenTypeFactory::isTokenValid(buf + nextChar)) { // check if it's operator of length 2
        buf += nextChar;
        in.get();
    } else if (!TokenTypeFactory::isTokenValid(buf)) { // otherwise check if it's not valid operator
        return false;
    }

    TokenType type = TokenTypeFactory::createTokenType(buf);
    token = Token(type, buf);

    return true;
}
