#pragma once

#include "Return.hpp"

namespace simpl {
    class Statement {
    public:
        virtual ~Statement() = default;
        virtual Return execute() = 0;
    };
}