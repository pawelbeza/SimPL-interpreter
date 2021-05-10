#include "Lexer.h"
#include "TokenType.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace simpl;

TEST(lexer, reading_token_before_first_advance_returns_eof_token) {
    std::istringstream in;
    Lexer lexer(in);

    ASSERT_EQ(lexer.getToken().getType(), TokenType::Eof);
}

TEST(lexer, scanning_empty_input_returns_eof_token) {
    std::istringstream in;
    Lexer lexer(in);
    lexer.readNextToken();

    ASSERT_EQ(lexer.getToken().getType(), TokenType::Eof);
}

TEST(lexer, lexer_returns_eof_after_last_token) {
    std::istringstream in("func");
    Lexer lexer(in);

    lexer.readNextToken();
    lexer.readNextToken();

    ASSERT_EQ(lexer.getToken().getType(), TokenType::Eof);
}

TEST(lexer, lexer_ignores_whitespaces) {
    std::istringstream in("      \t\n   func");
    Lexer lexer(in);
    lexer.readNextToken();

    ASSERT_EQ(lexer.getToken().getType(), TokenType::Function);
    ASSERT_EQ(lexer.getToken().getValue(), "func");
}

TEST(lexer, lexer_throws_unknown_token) {
    std::istringstream in("`");
    Lexer lexer(in);

    EXPECT_THROW(lexer.readNextToken(), std::runtime_error);
}

TEST(lexer, lexer_read_id) {
    std::istringstream in("id_321");
    Lexer lexer(in);
    lexer.readNextToken();

    ASSERT_EQ(lexer.getToken().getType(), TokenType::Id);
    ASSERT_EQ(lexer.getToken().getValue(), "id_321");
}

TEST(lexer, lexer_read_string) {
    std::istringstream in("\"text\"");
    Lexer lexer(in);
    lexer.readNextToken();

    ASSERT_EQ(lexer.getToken().getType(), TokenType::String);
    ASSERT_EQ(lexer.getToken().getValue(), "text");
}

TEST(lexer, lexer_read_string_with_white_chars) {
    std::istringstream in("\"\ttext\n\"");
    Lexer lexer(in);
    lexer.readNextToken();

    ASSERT_EQ(lexer.getToken().getType(), TokenType::String);
    ASSERT_EQ(lexer.getToken().getValue(), "\ttext\n");
}

TEST(lexer, lexer_read_int) {
    std::istringstream in("321");
    Lexer lexer(in);
    lexer.readNextToken();

    ASSERT_EQ(lexer.getToken().getType(), TokenType::Int);
    ASSERT_EQ(lexer.getToken().getValue(), "321");
}


TEST(lexer, lexer_read_const_tokens) {
    std::unordered_map<std::string, TokenType> types = TokenTypeFactory::getTokenTypes();

    std::string tokenTypes;
    for (auto &it : types)
        tokenTypes += it.first + " ";

    std::istringstream in(tokenTypes);
    Lexer lexer(in);

    for (auto &it : types) {
        lexer.readNextToken();

        ASSERT_EQ(lexer.getToken().getType(), it.second);
        ASSERT_EQ(lexer.getToken().getValue(), it.first);
    }

    lexer.readNextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::Eof);
}

