#pragma once

namespace simpl {
    class MathFactorExpression : public Expression {
    public:
        MathFactorExpression(std::vector<int> vec, bool minus_ = false) : minus(minus_) {
            variable = std::make_shared<Variable>(vec);
        }
        MathFactorExpression(std::shared_ptr <Statement> functionCall_, bool minus_ = false) :
                functionCall(functionCall_), minus(minus_) {}

        MathFactorExpression(std::shared_ptr <Expression> expression_, bool minus_ = false) :
                expression(expression_), minus(minus_) {}

        MathFactorExpression(std::string variableName_, bool minus_ = false) :
                variableName(variableName_), minus(minus_) {}

    private:
        bool minus;
        std::string variableName;
        std::shared_ptr <Variable> variable;
        std::shared_ptr <Statement> functionCall;
        std::shared_ptr <Expression> expression;
    };
}