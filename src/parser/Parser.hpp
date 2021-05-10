#pragma once

#include <Function.hpp>
#include "TokenType.h"
#include <Block.hpp>
#include "Lexer.h"

#include <list>
#include <vector>
#include <memory>
#include <unordered_set>

namespace simpl {
    class Parser {
    public:
        explicit Parser(Lexer &lexer);
        void parse();
    private:
        void parseProgram();
        std::shared_ptr<Function> parseFunc();
        std::vector<std::string> parseParameters();
        std::shared_ptr<Block> parseBlock();

        void advance();

        bool verifyTokenType(TokenType expected);
        Lexer lexer;

        void throwBadToken(const std::list<TokenType>&);

        Token acceptToken(TokenType expected);

        void parseIdPrefix();

        void parseWhile();

        void parseIf();

        void parseReturn();

        void parsePrint();

        void parseFuncCallSuffix();

        void parseVariableDefinitionSuffix();

        void parseVariableAssignmentSuffix();

        void parseFuncArgs();

        void parseLogicExpr();

        void parseLogicAndTerm();

        void parseLogicRelTerm();

        void parseLogicFactor();

        bool isTokenTypeRelational();

        void parseMathExp();

        bool isTokenTypeAdditive();

        void parseMathTerm();

        void parseMathFactor();

        bool isTokenTypeMultiplicative();

        void parseVec();

        void throwInvalidVec();
    };
}



