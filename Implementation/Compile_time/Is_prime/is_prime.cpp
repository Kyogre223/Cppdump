//
// Created by Lin Kai on 7/9/24.
//

#include "is_prime.h"



int main() {
    // find out if a number is prime

    std::cout << isPrime<7>::res << '\n';
    std::cout << isPrime<13>::res << '\n';
    std::cout << isPrime<4>::res << '\n';
    std::cout << isPrime<5>::res << '\n';
    std::cout << isPrime<200>::res << '\n';
    return 0;
}