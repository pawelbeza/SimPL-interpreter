#pragma once

#include "Variable.hpp"

namespace simpl {
    class Expression {
    public:
        virtual ~Expression() = default;
        virtual Variable calculate() const = 0;
    };
}