//
// Created by Lin Kai on 28/10/24.
//

#include <iostream>
#include <vector>


// size of an array?

template <size_t N, typename T>
void foo(T (&arr)[N]) {
    std::cout << "Size of " << N << ".With type as " << typeid(T).name() << '\n';
}

int main() {
    foo("Hello");



    return 0;
}
