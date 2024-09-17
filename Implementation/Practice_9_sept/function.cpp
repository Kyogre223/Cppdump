//
// Created by Lin Kai on 17/9/24.
//

#include "function.h"


int main() {
    auto can = [] <typename T, typename T2> (T a, T2 b) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    };

    can(2, 10);
    Function<void(int, int)> f = foo;
    f(2, 10);

    return 0;
}