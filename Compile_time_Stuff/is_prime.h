//
// Created by Lin Kai on 3/9/24.
//

#ifndef CPPDUMP_IS_PRIME_H
#define CPPDUMP_IS_PRIME_H

template <int I, int div>
struct IsPrime {
    constexpr static bool value = (I % div != 0) && IsPrime<I, div - 1>::value;
};

template <int I>
struct IsPrime<I, 2> {
    constexpr static bool value = (I % 2 != 0);
};

// Base case for when divisor reaches 1, the number is prime
template <int I>
struct IsPrime<I, 1> {
    constexpr static bool value = true;
};

// Specialization for edge cases: 0, 1 are not prime
template <>
struct IsPrime<0, 0> {
    constexpr static bool value = false;
};

template <>
struct IsPrime<1, 1> {
    constexpr static bool value = false;
};

// Wrapper to simplify usage
template <int I>
struct IsPrimeCheck {
    constexpr static bool value = IsPrime<I, I - 1>::value;
};

#endif //CPPDUMP_IS_PRIME_H
