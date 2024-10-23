//
// Created by Lin Kai on 22/10/24.
//


#include <iostream>
#include <compare>
#include <concepts>

void foo(auto T) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
}
struct A{
    A() {
        std::cout << "ctor\n";
    }
    A(A const& other) {
        std::cout << "cpy ctor\n";
    }

    A( A&& other) noexcept {
        std::cout << "Move ctor\n";
    }

    A& operator = (A&& other) noexcept {
        std::cout << "Move assign\n";
        return *this;
    }

    A& operator = (A const& other) {
        std::cout << "Copy assignment\n";
        return *this;
    }

    ~A() {
        std::cout << "Dtor\n";
    }

};

int main() {
    A a;
    foo(a);


    return 0;
}