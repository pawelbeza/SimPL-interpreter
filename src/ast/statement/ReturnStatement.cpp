#include "ReturnStatement.hpp"

#include <utility>

using namespace simpl;

ReturnStatement::ReturnStatement() : returnType(Return::Type::None) {}

ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expr_) : returnType(Return::Type::Variable), expr(std::move(expr_)) {}

Return ReturnStatement::execute() {
    return returnType == Return::Type::Variable ? Return(expr->calculate()) : Return();
}


