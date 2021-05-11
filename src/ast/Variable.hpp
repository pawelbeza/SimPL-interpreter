#pragma once

namespace simpl {
    class Variable {
    public:
        Variable() = default;
        explicit Variable(std::vector<int> numbers_) : numbers(numbers_) {}
    private:
        std::vector<int> numbers;
    };
}