#include "Parser.hpp"

#include "Function.hpp"
#include "Block.hpp"

#include <sstream>
#include <list>
#include <memory>
#include <vector>

using namespace simpl;

Parser::Parser(Lexer &lexer_) : lexer(lexer_) {}

void Parser::parse() {
    advance();
    parseProgram();
}

void Parser::parseProgram() {
    while (verifyTokenType(TokenType::Function))
        parseFunc();

    if (!verifyTokenType(TokenType::Eof))
        throwBadToken({TokenType::Eof});
}

std::shared_ptr<Function> Parser::parseFunc() {
    acceptToken(TokenType::Function);

    std::string funcID = acceptToken(TokenType::Id).getValue();

    acceptToken(TokenType::RoundBracketOpen);
    auto params = parseParameters();
    acceptToken(TokenType::RoundBracketClose);

    parseBlock();

    return std::make_shared<Function>(funcID, params);
}

std::vector<std::string> Parser::parseParameters() {
    std::vector<std::string> paramIDs;
    while (verifyTokenType(TokenType::Id)) {
        std::string paramID = acceptToken(TokenType::Id).getValue();
        paramIDs.push_back(paramID);

        if (!verifyTokenType(TokenType::RoundBracketClose))
            acceptToken(TokenType::Comma);
    }

    return paramIDs;
}

std::shared_ptr<Block> Parser::parseBlock() {
    acceptToken(TokenType::CurlyBracketOpen);

    while (true) {
        if (verifyTokenType(TokenType::Id)) {
            parseIdPrefix();
        } else if (verifyTokenType(TokenType::While)) {
            parseWhile();
        } else if (verifyTokenType(TokenType::If)) {
            parseIf();
        } else if (verifyTokenType(TokenType::Return)) {
            parseReturn();
        } else if (verifyTokenType(TokenType::Print)) {
            parsePrint();
        } else if (verifyTokenType(TokenType::CurlyBracketClose)) {
            advance();
            break;
        } else if (verifyTokenType(TokenType::CurlyBracketOpen)) {
            parseBlock();
        } else {
            throwBadToken({TokenType::Id, TokenType::While, TokenType::If, TokenType::Return, TokenType::Print,
                           TokenType::CurlyBracketClose});
        }
    }

    return std::make_shared<Block>();
}

void Parser::parseIdPrefix() {
    acceptToken(TokenType::Id);

    if (verifyTokenType(TokenType::RoundBracketOpen))
        parseFuncCallSuffix();
    else if (verifyTokenType(TokenType::Definition))
        parseVariableDefinitionSuffix();
    else if (verifyTokenType(TokenType::Assignment))
        parseVariableAssignmentSuffix();
    else
        throwBadToken({TokenType::CurlyBracketOpen, TokenType::Definition, TokenType::Assignment});

    acceptToken(TokenType::Semicolon);
}

void Parser::parseFuncCallSuffix() {
    acceptToken(TokenType::RoundBracketOpen);
    parseFuncArgs();
    acceptToken(TokenType::RoundBracketClose);
}

void Parser::parseVariableDefinitionSuffix() {
    acceptToken(TokenType::Definition);
    parseLogicExpr();
}

void Parser::parseVariableAssignmentSuffix() {
    acceptToken(TokenType::Assignment);
    parseLogicExpr();
}

void Parser::parseWhile() {
    acceptToken(TokenType::While);
    acceptToken(TokenType::RoundBracketOpen);
    parseLogicExpr();
    acceptToken(TokenType::RoundBracketClose);
    parseBlock();
}

void Parser::parseIf() {
    acceptToken(TokenType::If);
    acceptToken(TokenType::RoundBracketOpen);
    parseLogicExpr();
    acceptToken(TokenType::RoundBracketClose);
    parseBlock();

    if (!verifyTokenType(TokenType::Else))
        return;

    advance();
    parseBlock();
}

void Parser::parseReturn() {
    acceptToken(TokenType::Return);
    parseLogicExpr();

    acceptToken(TokenType::Semicolon);
}

void Parser::parsePrint() {
    acceptToken(TokenType::Print);
    acceptToken(TokenType::RoundBracketOpen);

    if (verifyTokenType(TokenType::String)) {
        advance();
    } else if (verifyTokenType(TokenType::RoundBracketClose)) {
        advance();
    } else {
        parseLogicExpr();
    }

    while (verifyTokenType(TokenType::Comma)) {
        acceptToken(TokenType::Comma);

        if (verifyTokenType(TokenType::String)) {
            advance();
        } else if (verifyTokenType(TokenType::RoundBracketClose)) {
            advance();
            break;
        } else {
            parseLogicExpr();
        }
    }

    acceptToken(TokenType::RoundBracketClose);
    acceptToken(TokenType::Semicolon);
}

void Parser::parseFuncArgs() {
    while (!verifyTokenType(TokenType::RoundBracketClose)) {
        parseLogicExpr();

        if (!verifyTokenType(TokenType::RoundBracketClose))
            acceptToken(TokenType::Comma);
    }
}

void Parser::parseLogicExpr() {
    parseLogicAndTerm();
    while (verifyTokenType(TokenType::Or)) {
        acceptToken(TokenType::Or);
        parseLogicAndTerm();
    }
}

void Parser::parseLogicAndTerm() {
    parseLogicRelTerm();
    while (verifyTokenType(TokenType::And)) {
        acceptToken(TokenType::And);
        parseLogicRelTerm();
    }
}

void Parser::parseLogicRelTerm() {
    parseLogicFactor();
    while (isTokenTypeRelational()) {
        advance();
        parseLogicFactor();
    }
}

void Parser::parseLogicFactor() {
    if (verifyTokenType(TokenType::Negation)) {
        acceptToken(TokenType::Negation);
        parseLogicFactor();
    } else {
        parseMathExp();
    }
}

void Parser::parseMathExp() {
    parseMathTerm();
    while (isTokenTypeAdditive()) {
        advance();
        parseMathTerm();
    }
}

void Parser::parseMathTerm() {
    parseMathFactor();
    while (isTokenTypeMultiplicative()) {
        advance();
        parseMathFactor();
    }
}

void Parser::parseMathFactor() {
    if (verifyTokenType(TokenType::RoundBracketOpen)) {
        acceptToken(TokenType::RoundBracketOpen);
        parseLogicExpr();
        acceptToken(TokenType::RoundBracketClose);
    } else if (verifyTokenType(TokenType::Minus)) {
        acceptToken(TokenType::Minus);
        parseMathFactor();
    } else if (verifyTokenType(TokenType::Int)) {
        acceptToken(TokenType::Int);
    } else if (verifyTokenType(TokenType::SquareBracketOpen)) {
        parseVec();
    } else if (verifyTokenType(TokenType::Id)) {
        acceptToken(TokenType::Id);
        if (verifyTokenType(TokenType::RoundBracketOpen))
            parseFuncCallSuffix();
        else {}
    } else {
        throwBadToken({TokenType::RoundBracketOpen, TokenType::Minus, TokenType::Int, TokenType::SquareBracketOpen,
                       TokenType::Id});
    }
}

void Parser::parseVec() {
    acceptToken(TokenType::SquareBracketOpen);

    acceptToken(TokenType::Int);
    int dimensions = 1;
    while(verifyTokenType(TokenType::Comma)) {
        acceptToken(TokenType::Comma);
        acceptToken(TokenType::Int);
        dimensions++;
    }

    if (dimensions == 1 || dimensions > 3)
        throwInvalidVec();

    acceptToken(TokenType::SquareBracketClose);
}

void Parser::advance() {
    lexer.readNextToken();
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

