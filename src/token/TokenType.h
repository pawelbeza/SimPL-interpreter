#pragma once

namespace simpl {
    enum class TokenType {
        Function,
        While,
        Return,
        If,
        Else,
        Print,

        Plus,
        Minus,
        ScalarMultiply,
        VectorMultiply,
        Divide,
        Modulo,
        Equality,
        Inequality,
        Less,
        LessOrEqual,
        Greater,
        GreaterOrEqual,
        Negation,
        And,
        Or,

        RoundBracketOpen,
        RoundBracketClose,
        CurlyBracketOpen,
        CurlyBracketClose,
        SquareBracketOpen,
        SquareBracketClose,
        Comma,
        Semicolon,
        Definition,
        Assignment,

        Id,
        String,
        Int,

        Eof,
    };
}