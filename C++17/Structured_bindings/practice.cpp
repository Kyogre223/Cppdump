//
// Created by Lin Kai on 28/10/24.
//

#include <iostream>



// revise structured bindings
// tuple size
// tuple element
// get

struct A {


public:
    A(int x ,int y):a{x}, b{y}{}
    int getA() const {
        return a;
    }

    int getB() const {
        return b;
    }
private:
    int a;
    int b;
};


// tuple size
template <>
struct std::tuple_size<A> {
    constexpr static size_t value = 2;
};

// tuple element

template <>
struct std::tuple_element<0, A> {
    using type = int;
};

template <>
struct std::tuple_element<1, A> {
    using type = int;
};

template <size_t I>
auto get(A const& a);

template <>
auto get<0>(A const& a) {
    return a.getA();
}

template <>
auto get<1>(A const& b) {
    return b.getB();
}





int main() {

    auto [c, d] = A(2, 5);

    // A a{2, 5};
    return 0;
}
