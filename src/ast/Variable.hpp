#pragma once

#include <vector>
#include "ostream"

namespace simpl {
    class Variable {
    public:
        Variable() = default;
        explicit Variable(const std::vector<int>& numbers_);
        Variable& operator=(const Variable& rhs);

        int& operator[](int index);
        std::vector<int>& operator*();

        Variable operator<(const Variable& rhs) const;
        Variable operator> (const Variable& rhs) const;
        Variable operator<=(const Variable& rhs) const;
        Variable operator>=(const Variable& rhs) const;

        Variable operator==(const Variable& rhs) const;
        Variable operator!=(const Variable& rhs) const;

        Variable operator+() const;
        Variable operator-() const;

        Variable operator+(const Variable &rhs) const;
        Variable operator-(const Variable &rhs) const;
        Variable operator*(const Variable &rhs) const;
        Variable operator/(const Variable &rhs) const;
        Variable operator%(const Variable &rhs) const;

        Variable operator&&(const Variable &rhs) const;
        Variable operator||(const Variable &rhs) const;
        Variable vectorProduct(const Variable &rhs) const;

        operator bool() const;
        Variable operator!() const;

        std::string toString() const;
        unsigned int size() const;
    private:
        static Variable varTrue() ;
        static Variable varFalse() ;

        std::vector<int> numbers;
    };

    inline std::ostream &operator<<(std::ostream &os, const Variable &var) {
        return os << var.toString();
    }
}