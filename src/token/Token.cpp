#include "Token.h"

#include <utility>

using namespace simpl;

Token::Token(const TokenType &type_, std::string value_) : type(type_), value(std::move(value_)) {}