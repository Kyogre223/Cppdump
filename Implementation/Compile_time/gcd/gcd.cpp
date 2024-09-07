//
// Created by Lin Kai on 7/9/24.
//

#include "gcd.h"


int main() {
    // find gcd at compile time
    std::cout << gcd<5, 15>::value << '\n';

    std::cout << gcd<15, 5>::value << "\n";


    return 0;
}