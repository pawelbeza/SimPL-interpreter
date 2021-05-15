#include "Parser.hpp"

#include <Function.hpp>
#include <FunctionCallStatement.hpp>
#include <IfStatement.hpp>
#include <Block.hpp>
#include <Program.hpp>
#include <VariableAssignment.hpp>
#include <WhileStatement.hpp>
#include <ReturnStatement.hpp>
#include <PrintStatement.hpp>

#include <sstream>
#include <list>
#include <memory>
#include <vector>
#include <LogicExpression.hpp>
#include <RelationalExpression.hpp>
#include <LogicFactorExpression.hpp>
#include <MathExpression.hpp>
#include <MathFactorExpression.hpp>

using namespace simpl;

Parser::Parser(Lexer &lexer_) : lexer(lexer_) {}

void Parser::parse() {
    advance();
    parseProgram();
}

void Parser::parseProgram() {
    program = std::make_shared<Program>();

    while (verifyTokenType(TokenType::Function))
        parseFunc();

    if (!verifyTokenType(TokenType::Eof))
        throwBadToken({TokenType::Eof});
}

void Parser::parseFunc() {
    acceptToken(TokenType::Function);

    std::string funcID = acceptToken(TokenType::Id).getValue();

    acceptToken(TokenType::RoundBracketOpen);
    auto params = parseParameters();
    acceptToken(TokenType::RoundBracketClose);

    auto func = std::make_shared<Function>(funcID, params);
    program->addFunction(func);

    parseBlock(func->getBlock());
}

std::vector<std::string> Parser::parseParameters() {
    std::vector<std::string> paramIDs;

    if (!verifyTokenType(TokenType::RoundBracketClose)) {
        std::string paramID = acceptToken(TokenType::Id).getValue();
        paramIDs.push_back(paramID);
    }

    while (verifyTokenType(TokenType::Comma)) {
        advance();

        std::string paramID = acceptToken(TokenType::Id).getValue();
        paramIDs.push_back(paramID);
    }

    return paramIDs;
}

void Parser::parseBlock(const std::shared_ptr<Block>& parentBlock) {
    acceptToken(TokenType::CurlyBracketOpen);

    while (true) {
        std::shared_ptr<Statement> statement;
        if (verifyTokenType(TokenType::Id)) {
            statement = parseIdPrefix(parentBlock);
        } else if (verifyTokenType(TokenType::While)) {
            statement = parseWhile(parentBlock);
        } else if (verifyTokenType(TokenType::If)) {
            statement = parseIf(parentBlock);
        } else if (verifyTokenType(TokenType::Return)) {
            statement = parseReturn(parentBlock);
        } else if (verifyTokenType(TokenType::Print)) {
            statement = parsePrint(parentBlock);
        } else if (verifyTokenType(TokenType::CurlyBracketClose)) {
            advance();
            break;
        } else if (verifyTokenType(TokenType::CurlyBracketOpen)) {
            auto childBlock = std::make_shared<Block>(parentBlock);
            parseBlock(childBlock);
        } else {
            throwBadToken({TokenType::Id, TokenType::While, TokenType::If, TokenType::Return, TokenType::Print,
                           TokenType::CurlyBracketClose});
        }

        parentBlock->addStatement(statement);
    }
}

std::shared_ptr<Statement> Parser::parseIdPrefix(const std::shared_ptr<Block>& parentBlock) {
    Token token = acceptToken(TokenType::Id);

    std::shared_ptr<Statement> statement;
    if (verifyTokenType(TokenType::RoundBracketOpen))
        statement = parseFuncCallSuffix(parentBlock, token);
    else if (verifyTokenType(TokenType::Definition))
        statement = parseVariableDefinitionSuffix(parentBlock, token);
    else if (verifyTokenType(TokenType::Assignment))
        statement = parseVariableAssignmentSuffix(parentBlock, token);
    else
        throwBadToken({TokenType::CurlyBracketOpen, TokenType::Definition, TokenType::Assignment});

    acceptToken(TokenType::Semicolon);

    return statement;
}

std::shared_ptr<Statement> Parser::parseFuncCallSuffix(const std::shared_ptr<Block>& parentBlock, const Token& token) {
    std::string funcName = token.getValue();
    if(!program->functionExists(funcName))
        throwFunctionNotExist(funcName);

    std::shared_ptr<Function> func = program->getFunction(funcName);

    acceptToken(TokenType::RoundBracketOpen);

    auto args = parseFuncArgs(parentBlock);
    if (paramsValid(func, args))
        throwFunctionInvalidParametersNumber(func, args.size());

    acceptToken(TokenType::RoundBracketClose);

    return std::make_shared<FunctionCallStatement>(func, args);
}

std::shared_ptr<Statement> Parser::parseVariableDefinitionSuffix(const std::shared_ptr<Block>& parentBlock, const Token& token) {
    std::string varName = token.getValue();
    if (parentBlock->existsVariable(varName))
        throwVariableAlreadyExists(varName);

    parentBlock->addVariable(varName);

    acceptToken(TokenType::Definition);
    auto expr = parseLogicExpr(parentBlock);

    return std::make_shared<VariableAssignment>(varName, expr);
}

std::shared_ptr<Statement> Parser::parseVariableAssignmentSuffix(const std::shared_ptr<Block>& parentBlock, const Token& token) {
    std::string varName = token.getValue();
    if (!parentBlock->existsVariable(varName))
        throwVariableNotExists(varName);

    acceptToken(TokenType::Assignment);
    auto expr = parseLogicExpr(parentBlock);

    return std::make_shared<VariableAssignment>(varName, expr);
}

std::shared_ptr<Statement> Parser::parseWhile(const std::shared_ptr<Block>& parentBlock) {
    acceptToken(TokenType::While);
    acceptToken(TokenType::RoundBracketOpen);
    auto expr = parseLogicExpr(parentBlock);
    acceptToken(TokenType::RoundBracketClose);

    auto childBlock = std::make_shared<Block>(parentBlock);
    parseBlock(childBlock);

    return std::make_shared<WhileStatement>(expr, childBlock);
}

std::shared_ptr<Statement> Parser::parseIf(const std::shared_ptr<Block>& parentBlock) {
    acceptToken(TokenType::If);

    acceptToken(TokenType::RoundBracketOpen);
    auto expr = parseLogicExpr(parentBlock);
    acceptToken(TokenType::RoundBracketClose);

    auto blockIf = std::make_shared<Block>(parentBlock);
    parseBlock(blockIf);

    if (!verifyTokenType(TokenType::Else))
        return std::make_shared<IfStatement>(expr, blockIf);

    advance();

    auto blockElse = std::make_shared<Block>(parentBlock);
    parseBlock(blockElse);

    return std::make_shared<IfStatement>(expr, blockIf, blockElse);
}

std::shared_ptr<Statement> Parser::parseReturn(const std::shared_ptr<Block>& parentBlock) {
    acceptToken(TokenType::Return);
    auto expr = parseLogicExpr(parentBlock);
    acceptToken(TokenType::Semicolon);

    return std::make_shared<ReturnStatement>(expr);
}

std::shared_ptr<Statement> Parser::parsePrint(const std::shared_ptr<Block>& parentBlock) {
    acceptToken(TokenType::Print);
    acceptToken(TokenType::RoundBracketOpen);

    auto printStatement = std::make_shared<PrintStatement>();
    if (verifyTokenType(TokenType::String)) {
        std::string arg = acceptToken(TokenType::String).getValue();
        printStatement->addPrintArg(arg);
    } else if (verifyTokenType(TokenType::RoundBracketClose)) {
        advance();
    } else {
        auto expr = parseLogicExpr(parentBlock);
        printStatement->addPrintArg(expr);
    }

    while (verifyTokenType(TokenType::Comma)) {
        advance();

        if (verifyTokenType(TokenType::String)) {
            std::string arg = acceptToken(TokenType::String).getValue();
            printStatement->addPrintArg(arg);
        } else if (verifyTokenType(TokenType::RoundBracketClose)) {
            advance();
            break;
        } else {
            auto expr = parseLogicExpr(parentBlock);
            printStatement->addPrintArg(expr);
        }
    }

    acceptToken(TokenType::RoundBracketClose);
    acceptToken(TokenType::Semicolon);

    return printStatement;
}

std::vector<std::shared_ptr<Expression>> Parser::parseFuncArgs(const std::shared_ptr<Block>& parentBlock) {
    std::vector<std::shared_ptr<Expression>> args;

    if (!verifyTokenType(TokenType::RoundBracketClose)) {
        auto arg = parseLogicExpr(parentBlock);
        args.push_back(arg);
    }

    while (verifyTokenType(TokenType::Comma)) {
        advance();

        auto arg = parseLogicExpr(parentBlock);
        args.push_back(arg);
    }

    return args;
}

std::shared_ptr<Expression> Parser::parseLogicExpr(const std::shared_ptr<Block>& parentBlock) {
    std::vector<std::shared_ptr<Expression>> andExpressions;

    std::shared_ptr<AndExpression> expression;
    andExpressions.push_back(expression);

    auto term = parseLogicAndTerm(parentBlock);
    andExpressions.push_back(term);

    while (verifyTokenType(TokenType::Or)) {
        advance();

        term = parseLogicAndTerm(parentBlock);
        andExpressions.push_back(term);
    }

    return std::make_shared<LogicExpression>(andExpressions);
}

std::shared_ptr<AndExpression> Parser::parseLogicAndTerm(const std::shared_ptr<Block>& parentBlock) {
    std::vector<std::shared_ptr<Expression>> relExpressions;

    auto term = parseLogicRelTerm(parentBlock);
    relExpressions.push_back(term);

    while (verifyTokenType(TokenType::And)) {
        advance();

        term = parseLogicRelTerm(parentBlock);
        relExpressions.push_back(term);
    }

    return std::make_shared<AndExpression>(relExpressions);
}

std::shared_ptr<RelationalExpression> Parser::parseLogicRelTerm(const std::shared_ptr<Block>& parentBlock) {
    std::vector<std::shared_ptr<Expression>> factorExpressions;
    std::vector<TokenType> relOps;

    auto factor = parseLogicFactor(parentBlock);
    factorExpressions.push_back(factor);

    while (isTokenTypeRelational()) {
        TokenType type = advance().getType();
        relOps.push_back(type);

        factor = parseLogicFactor(parentBlock);
        factorExpressions.push_back(factor);
    }

    return std::make_shared<RelationalExpression>(factorExpressions, relOps);
}

std::shared_ptr<Expression> Parser::parseLogicFactor(const std::shared_ptr<Block>& parentBlock) {
    if (verifyTokenType(TokenType::Negation)) {
        advance();

        auto factor = parseMathExp(parentBlock);
        return std::make_shared<LogicFactorExpression>(factor, true);
    } else {
        auto factor = parseMathExp(parentBlock);
        return std::make_shared<LogicFactorExpression>(factor, false);
    }
}

std::shared_ptr<Expression> Parser::parseMathExp(const std::shared_ptr<Block>& parentBlock) {
    std::vector<std::shared_ptr<Expression>> termExpressions;
    std::vector<TokenType> additiveOps;

    auto term = parseMathTerm(parentBlock);
    termExpressions.push_back(term);

    while (isTokenTypeAdditive()) {
        TokenType type = advance().getType();
        additiveOps.push_back(type);

        term = parseMathTerm(parentBlock);
        termExpressions.push_back(term);
    }

    return std::make_shared<MathExpression>(termExpressions, additiveOps);
}

std::shared_ptr<Expression> Parser::parseMathTerm(const std::shared_ptr<Block>& parentBlock) {
    std::vector<std::shared_ptr<Expression>> factorExpressions;
    std::vector<TokenType> multiplicativeOps;

    auto factor = parseMathFactor(parentBlock);
    factorExpressions.push_back(factor);

    while (isTokenTypeMultiplicative()) {
        TokenType type = advance().getType();
        multiplicativeOps.push_back(type);

        factor = parseMathFactor(parentBlock);
        factorExpressions.push_back(factor);
    }

    return std::make_shared<MathTermExpression>(factorExpressions, multiplicativeOps);
}

std::shared_ptr<Expression> Parser::parseMathFactor(const std::shared_ptr<Block>& parentBlock) {
    std::shared_ptr<Expression> expr;
    bool minus = false;

    if (verifyTokenType(TokenType::RoundBracketOpen)) {
        advance();

        auto nextExpr = parseLogicExpr(parentBlock);
        expr = std::make_shared<MathFactorExpression>(nextExpr);

        acceptToken(TokenType::RoundBracketClose);
    } else if (verifyTokenType(TokenType::Minus)) {
        advance();

        auto factor = parseMathFactor(parentBlock);
        expr = std::make_shared<MathFactorExpression>(factor, true);
    } else if (verifyTokenType(TokenType::Int)) {
        std::string num = acceptToken(TokenType::Int).getValue();
        int number = std::stoi(num);

        auto var = std::make_shared<Variable>(std::vector<int>{number});
        expr = std::make_shared<MathFactorExpression>(var);
    } else if (verifyTokenType(TokenType::SquareBracketOpen)) {
        std::vector<int> vec = parseVec();

        auto var = std::make_shared<Variable>(vec);
        expr = std::make_shared<MathFactorExpression>(var);
    } else if (verifyTokenType(TokenType::Id)) {
        Token token = acceptToken(TokenType::Id);
        std:: string id = token.getValue();

        if (verifyTokenType(TokenType::RoundBracketOpen)) {
            auto funcCall = parseFuncCallSuffix(parentBlock, token);
            expr = std::make_shared<MathFactorExpression>(funcCall);
        } else if (parentBlock->existsVariable(id)) {
            Variable var = parentBlock->getVariable(id);

            auto mathVar = std::make_shared<Variable>(var);
            expr = std::make_shared<MathFactorExpression>(mathVar);
        } else {
            throwVariableNotExists(id);
        }
    } else {
        throwBadToken({TokenType::RoundBracketOpen, TokenType::Minus, TokenType::Int, TokenType::SquareBracketOpen,
                       TokenType::Id});
    }

    return expr;
}

std::vector<int> Parser::parseVec() {
    acceptToken(TokenType::SquareBracketOpen);

    std::vector<int> vec;

    std::string num = acceptToken(TokenType::Int).getValue();
    int number = std::stoi(num);
    vec.push_back(number);

    while(verifyTokenType(TokenType::Comma)) {
        advance();

        num = acceptToken(TokenType::Int).getValue();
        number = std::stoi(num);
        vec.push_back(number);
    }

    if (vec.size() == 1 || vec.size() > 3)
        throwInvalidVec();

    acceptToken(TokenType::SquareBracketClose);

    return vec;
}

Token Parser::advance() {
    Token token = lexer.getToken();
    lexer.readNextToken();

    return token;
}

Token Parser::acceptToken(TokenType expected) {
    if (!verifyTokenType(expected))
        throwBadToken({expected});

    Token token = lexer.getToken();
    advance();

    return token;
}

bool Parser::verifyTokenType(TokenType expected) {
    return lexer.getToken().getType() == expected;
}

bool Parser::isTokenTypeRelational() {
    TokenType type = lexer.getToken().getType();
    const std::unordered_set<TokenType> relOperators{TokenType::Equality, TokenType::Inequality, TokenType::Less,
                                                     TokenType::LessOrEqual, TokenType::Greater,
                                                     TokenType::GreaterOrEqual};
    return relOperators.find(type) != relOperators.end();
}

bool Parser::isTokenTypeAdditive() {
    TokenType type = lexer.getToken().getType();
    return type == TokenType::Plus || type == TokenType::Minus;
}

bool Parser::isTokenTypeMultiplicative() {
    TokenType type = lexer.getToken().getType();
    const std::unordered_set<TokenType> mulOperators{TokenType::ScalarMultiply, TokenType::VectorMultiply, TokenType::Divide,
                                                     TokenType::Modulo};
    return mulOperators.find(type) != mulOperators.end();
}

bool Parser::paramsValid(const std::shared_ptr<Function>& func, const std::vector<std::shared_ptr<Expression>>& args) {
    return func->getParametersNumber() != args.size();
}

void Parser::throwVariableNotExists(const std::string& varName) {
    std::string msg = "cannot assign value to variable \"" + varName + "\" , because variable wasn't defined";
    throw std::runtime_error(msg);
}

void Parser::throwVariableAlreadyExists(const std::string &varName) {
    std::string msg = "cannot initialize variable, because variable \"" + varName + "\" already exists";
    throw std::runtime_error(msg);
}

void Parser::throwFunctionInvalidParametersNumber(const std::shared_ptr<Function>& func, int actualParamsNum) {
    std::string funcName = func->getID();
    int expectedParamsNum = func->getParametersNumber();

    std::string msg = "function \"" + funcName + "\" expects " + std::to_string(expectedParamsNum) + ", got " +
            std::to_string(actualParamsNum);
    throw std::runtime_error(msg);
}

void Parser::throwFunctionNotExist(const std::string& funcName) {
    std::string msg = "function with name \"" + funcName + "\" doesn't exist";
    throw std::runtime_error(msg);
}

void Parser::throwInvalidVec() {
    std::string msg = "invalid vector size, support only 2d and 3d vectors";
    throw std::runtime_error(msg);
}

void Parser::throwBadToken(const std::list<TokenType> &expectedTokens) {
    std::stringstream ss;
    ss << "Expected one of the tokens: ";
    for (auto tokenType : expectedTokens)
        ss << tokenType << " ";
    ss << "Received token: " << lexer.getToken().getType();

    throw std::runtime_error(ss.str());
}
