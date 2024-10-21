//
// Created by Lin Kai on 21/10/24.
//

#include <iostream>
#include <compare>

template <typename T>
struct Base {
    void foo() {
        std::cout << "foo\n";
    }
};


template <typename T>
struct Child: Base<T> {
    void bar() {
        this->foo(); // this-> is important.
    }
};

void foo() {
    std::cout << "Global foo\n";
}


int main() {



    return 0;
}
