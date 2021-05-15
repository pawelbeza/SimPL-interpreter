#pragma once

namespace simpl {
    class Expression {
    public:
        virtual ~Expression() = default;
        virtual Variable calculate() const = 0;
    };
}