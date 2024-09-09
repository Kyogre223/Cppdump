//
// Created by Lin Kai on 9/9/24.
//

#ifndef CPPDUMP_VARIANT_H
#define CPPDUMP_VARIANT_H


#include <bits/stdc++.h>


template <typename...>
struct helper {
};

template <typename T>
struct helper<T> {
    constexpr static int value = -1e5;
};

template <typename T, typename...Ts>
struct helper<T, T, Ts...> {
    constexpr static int value = 0;
};

template <typename T, typename U, typename... Ts>
struct helper<T, U, Ts...> {
    constexpr static int value = 1 + helper<T, Ts...>::value;
};


template <typename T, typename... Ts>
union recursive_union {
    T data_;
    recursive_union<Ts...> storage_;
    template <int I, typename U>
    recursive_union(std::integral_constant<int, I>, U&& data):storage_(std::integral_constant<int, I - 1>{}, std::forward<U>(data)) {

    }
    template <typename U>
    recursive_union(std::integral_constant<int, 0>, U&& data):data_(data){

    }
    template <int I>
    auto& get() {
        if constexpr (I == 0) {
            return data_;
        } else {
            return storage_.template get<I - 1>();
        }
    }

    ~recursive_union(){};

};


template <typename T>
union recursive_union<T> {
    T data_;
    template <typename U>
    recursive_union(U&& u):data_(std::forward<U>(u)){}
    ~recursive_union(){};
    template <int I>
    auto& get() {
        return data_;
    }

};



template <typename... Types>
struct myVariant {

    recursive_union<Types...>data_;
    int index_;
    template <typename T>
    myVariant(T&& data): data_(std::integral_constant<int, helper<T, Types...>::value>(), std::forward<T>(data)), index_(helper<T, Types...>::value) {

    }

    template <int I>
    auto& get() {
        if (index_ != I) {
            throw std::bad_variant_access();
        }
        return data_.template get<I>();
    }

};

#endif //CPPDUMP_VARIANT_H
