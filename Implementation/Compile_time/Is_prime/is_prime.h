//
// Created by Lin Kai on 7/9/24.
//

#ifndef CPPDUMP_IS_PRIME_H
#define CPPDUMP_IS_PRIME_H


template <int A, int B>
struct helper {
    constexpr static bool res = (A % B != 0) && helper<A, B - 1>::res;
};

template <int I>
struct helper<I, 1> {
    constexpr static bool res = true;
};

template <int I>
struct isPrime {
    // this helper
    constexpr static bool res = helper<I, I - 1>::res;
};


#endif //CPPDUMP_IS_PRIME_H
