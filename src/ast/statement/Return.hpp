#pragma once

#include "Variable.hpp"

namespace simpl {
    struct Return {
        enum class Type {
            Variable,
            None
        };

        explicit Return() : type(Type::None) {}
        explicit Return(const Variable& var_) : type(Type::Variable), var(var_) {}

        Type type;
        Variable var;
    };
}