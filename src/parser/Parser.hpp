#pragma once

#include <Program.hpp>
#include <Expression.hpp>
#include <Function.hpp>
#include "TokenType.h"
#include <Block.hpp>

#include "Lexer.h"
#include <list>
#include <vector>
#include <memory>
#include <unordered_set>
#include <AndExpression.hpp>
#include <LogicFactorExpression.hpp>

namespace simpl {
    class Parser {
    public:
        explicit Parser(Lexer &lexer);
        void parse();
    private:
        void parseProgram();
        void parseFunc();
        void parseBlock(const std::shared_ptr<Block>& block);

        std::vector<std::string> parseParameters();
        std::shared_ptr<Statement> parseIdPrefix(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Statement> parseWhile(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Statement> parseIf(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Statement> parseReturn(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Statement> parsePrint(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Statement> parseFuncCallSuffix(const std::shared_ptr<Block>& parentBlock, const Token& token);
        std::shared_ptr<Statement> parseVariableDefinitionSuffix(const std::shared_ptr<Block>& parentBlock, const Token& token);
        std::shared_ptr<Statement> parseVariableAssignmentSuffix(const std::shared_ptr<Block>& parentBlock, const Token& token);

        std::vector<std::shared_ptr<Expression>> parseFuncArgs(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Expression> parseLogicExpr(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<AndExpression> parseLogicAndTerm(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<RelationalExpression> parseLogicRelTerm(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Expression> parseLogicFactor(const std::shared_ptr<Block>& parentBlock);

        std::shared_ptr<Expression> parseMathExp(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Expression> parseMathTerm(const std::shared_ptr<Block>& parentBlock);
        std::shared_ptr<Expression> parseMathFactor(const std::shared_ptr<Block>& parentBlock);

        void advance();
        std::vector<int> parseVec();
        Token acceptToken(TokenType expected);
        bool verifyTokenType(TokenType expected);

        bool isTokenTypeAdditive();
        bool isTokenTypeRelational();
        bool isTokenTypeMultiplicative();
        bool paramsValid(const std::shared_ptr<Function> &func, const std::vector<std::shared_ptr<Expression>> &args);

        void throwInvalidVec();
        void throwBadToken(const std::list<TokenType>&);
        void throwFunctionNotExist(const std::string& funcName);
        void throwVariableNotExists(const std::string& varName);
        void throwVariableAlreadyExists(const std::string& varName);
        void throwFunctionInvalidParametersNumber(const std::shared_ptr<Function>& func, int actualParamsNum);

        Lexer lexer;
        std::shared_ptr<Program> program;
    };
}



