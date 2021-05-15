#include "Variable.hpp"

using namespace simpl;

Variable::Variable(const std::vector<int> &numbers_) {
    numbers = numbers_;
}

Variable &Variable::operator=(const Variable &rhs) {
    if (this == &rhs)
        return *this;

    numbers = rhs.numbers;
    return *this;
}

int &Variable::operator[](int index) {
    return numbers[index];
}

std::vector<int> &Variable::operator*() {
    return numbers;
}

Variable Variable::operator<(const Variable &rhs) const {
    return numbers < rhs.numbers ? varTrue() : varFalse();
}

Variable Variable::operator>(const Variable &rhs) const {
    return rhs < *this;
}

Variable Variable::operator<=(const Variable &rhs) const {
    return !(*this > rhs);
}

Variable Variable::operator>=(const Variable &rhs) const {
    return !(*this < rhs);
}

Variable Variable::operator==(const Variable &rhs) const {
    return numbers == rhs.numbers ? varTrue() : varFalse();
}

Variable Variable::operator!=(const Variable &rhs) const {
    return !(rhs == *this);
}

Variable Variable::varTrue() {
    return Variable({1});
}

Variable Variable::varFalse() {
    return Variable({0});
}

Variable Variable::operator+() const {
    return *this;
}

Variable Variable::operator-() const {
    Variable var(std::vector<int>(numbers.size()));
    for (int i = 0; i < numbers.size(); i++)
        var[i] = -numbers[i];

    return var;
}

Variable Variable::operator+(const Variable &rhs) const {
    if (this->size() != rhs.size())
        throw std::runtime_error("couldn't add because of dimensions mismatch: left variable size: " +
                                 std::to_string(this->size()) + ", right variable size: " + std::to_string(rhs.size()));

    Variable var = *this;
    for (int i = 0; i < rhs.size(); i++)
        var[i] += rhs.numbers[i];

    return var;
}

Variable Variable::operator-(const Variable &rhs) const {
    if (this->size() != rhs.size())
        throw std::runtime_error("couldn't subtract because of dimensions mismatch: left variable size: " +
                                 std::to_string(this->size()) + ", right variable size: " + std::to_string(rhs.size()));

    Variable var = *this;
    for (int i = 0; i < rhs.size(); i++)
        var[i] -= rhs.numbers[i];

    return var;
}

Variable Variable::operator*(const Variable &rhs) const {
    if (this->size() != rhs.size())
        throw std::runtime_error("couldn't multiply because of dimensions mismatch: left variable size: " +
                                 std::to_string(this->size()) + ", right variable size: " + std::to_string(rhs.size()));

    int res = 0;
    for (int i = 0; i < rhs.size(); i++)
        res += this->numbers[i] * rhs.numbers[i];

    return Variable({res});
}

simpl::Variable simpl::Variable::vectorProduct(const simpl::Variable &rhs) const {
    if (this->size() != rhs.size())
        throw std::runtime_error("couldn't multiply because of dimensions mismatch: left variable size: " +
                                 std::to_string(this->size()) + ", right variable size: " + std::to_string(rhs.size()));

    int dim1, dim2, dim3;
    switch (rhs.size()) {
        case 0:
        case 1:
            return Variable();
        case 2:
            dim1 = this->numbers[1] - rhs.numbers[1];
            dim2 = rhs.numbers[0] - this->numbers[0];
            return Variable({dim1, dim2});
        default:
            dim1 = this->numbers[1] * rhs.numbers[2] - this->numbers[2] * rhs.numbers[1];
            dim2 = this->numbers[2] * rhs.numbers[0] - this->numbers[0] * rhs.numbers[2];
            dim3 = this->numbers[0] * rhs.numbers[1] - this->numbers[1] * rhs.numbers[0];
            return Variable({dim1, dim2, dim3});
    }
}

Variable Variable::operator/(const Variable &rhs) const {
    if (this->size() != rhs.size())
        throw std::runtime_error("couldn't divide because of dimensions mismatch: left variable size: " +
                                 std::to_string(this->size()) + ", right variable size: " + std::to_string(rhs.size()));

    Variable var = *this;
    for (int i = 0; i < rhs.size(); i++) {
        if (rhs.numbers[i] == 0)
            throw std::runtime_error("couldn't divide by zero");

        var[i] /= rhs.numbers[i];
    }

    return var;
}

Variable Variable::operator%(const Variable &rhs) const {
    if (this->size() != rhs.size())
        throw std::runtime_error("couldn't modulo because of dimensions mismatch: left variable size: " +
                                 std::to_string(this->size()) + ", right variable size: " + std::to_string(rhs.size()));

    Variable var = *this;
    for (int i = 0; i < rhs.size(); i++) {
        if (rhs.numbers[i] == 0)
            throw std::runtime_error("couldn't modulo by zero");

        var[i] %= rhs.numbers[i];
    }

    return var;
}

Variable Variable::operator&&(const Variable &rhs) const {
    return static_cast<bool>(*this) && static_cast<bool>(rhs) ? varTrue() : varFalse();
}

Variable Variable::operator||(const Variable &rhs) const {
    return static_cast<bool>(*this) || static_cast<bool>(rhs) ? varTrue() : varFalse();
}

Variable::operator bool() const {
    return numbers != std::vector<int>({0});
}

Variable Variable::operator!() const {
    return *this ? varFalse() : varTrue();
}

std::string simpl::Variable::toString() const {
    std::string str = "[";
    for (int i = 0; i < numbers.size(); i++) {
        str += std::to_string(numbers[i]);

        if (i != numbers.size() - 1)
            str += ", ";
    }
    str += "]";
    return str;
}

unsigned int Variable::size() const {
    return numbers.size();
}
