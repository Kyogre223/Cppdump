//
// Created by Lin Kai on 26/10/24.
//

#include <iostream>


struct A {
    int a;
    int b;
};


// overload the tuple size and tuple_element


struct B {
    B(int x, int y) {
        a = x;
        b = y;
    }
    int getA() const { return a; }

    int getB() const { return b; }
private:
    int a;
    int b;
};


template <>
struct std::tuple_size<B> {
    static constexpr size_t value = 2;
};

template <size_t N>
auto get(B const& b);

template <>
auto get<0>(B const& b) { return b.getA(); }

template <>
auto get<1>(B const& b) { return b.getB(); }


template <size_t N>
struct std::tuple_element<N, B> {
    using type = int;
};

int main() {
    // structured bindings tests.
    A a{2, 5};
    auto [c, d] = a; // OK
    std::cout << c << ' ' << d << '\n'; // OK

    B b{5, 10};// define constructor else no
    auto [x, y] = b;  // overload tuple size tuple element and get.

    return 0;
}
