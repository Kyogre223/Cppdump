//
// Created by Lin Kai on 7/9/24.
//

#ifndef CPPDUMP_GCD_H
#define CPPDUMP_GCD_H

#include <iostream>


template <int A, int B>
struct gcd {
    constexpr static int value = gcd<B, A% B>::value;
};

template <int I>
struct gcd<I, 0> {
    constexpr static int value = I;
};

#endif //CPPDUMP_GCD_H
