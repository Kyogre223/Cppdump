//
// Created by Lin Kai on 25/8/24.
//

#ifndef CPPDUMP_STD_VARIANT_H
#define CPPDUMP_STD_VARIANT_H


#include <iostream>
#include <bits/stdc++.h>


namespace Impl {

    template <typename...>
    struct helper;

    template <typename T, typename... Ts>
    struct helper<T, T, Ts...> {
        constexpr static int value = 0;
    };

    template <typename T, typename U, typename... Us>
    struct helper<T, U, Us...> {
        constexpr static int value = 1 + helper<T, Us...>::value;
    };

    template<typename T>
    struct helper<T> {
        constexpr static int value = -1e5;
    };

    template <typename T, typename... Alternatives>
    union recursive_union {
        T t_;
        recursive_union<Alternatives...>rest;

        template <typename U>
        recursive_union(std::integral_constant<int, 0>, U&& u): t_(std::forward<U>(u)){}

        template <int I, typename U>
        recursive_union(std::integral_constant<int, I>, U&& u):rest(std::integral_constant<int, I - 1>{}, std::forward<U>(u)) {

        }
        ~recursive_union(){}

        template <int I>
        auto& get() {
            if constexpr (I == 0) {
                return t_;
            } else {
                return rest.template get<I - 1>();
            }
        }

    };

    template <typename T>
    union recursive_union<T> {
        T t_;
        int index_;
        template <typename U>
        recursive_union(std::integral_constant<int, 0>, U&& u): t_{std::forward<U>(u)}{}

        ~recursive_union(){}

        template <int I>
        auto& get() {
            return t_;
        }
    };



}



namespace K {

    template <typename... Alternatives>
    struct MyVariant {
        int index_;
        Impl::recursive_union<Alternatives...> storage_;
        template <typename T>
        MyVariant(T&& t):index_(Impl::helper<T, Alternatives...>::value),
                         storage_(std::integral_constant<int, Impl::helper<T, Alternatives...>::value>{}, t) {
            assert(index_ >= 0);
        }
        int index() {
            return index_;
        }

        template <int I>
        auto& get() {
            return storage_.template get<I>();
        }
    };
}



#endif //CPPDUMP_STD_VARIANT_H
