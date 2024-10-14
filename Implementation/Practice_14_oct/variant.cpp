//
// Created by Lin Kai on 14/10/24.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>


template <typename... T>
struct helper;

template <typename T, typename... Others>
struct helper<T, T, Others...> {
    constexpr static int value = 0;
};

template <typename T, typename U, typename... Others>
struct helper<T, U, Others...> {
    constexpr static int value = 1 + helper<T, Others...>::value;
};

template <typename T>
struct helper<T> {
    constexpr static int value = -1e5;
};







template <typename CurType, typename... Alternatives>
union RecursiveUnion {

    template <typename U, int I>
    RecursiveUnion(U&& data, std::integral_constant<int, I>):storage_(std::forward<U>(data), std::integral_constant<int, I - 1>{}){}

    template <typename U>
    RecursiveUnion(U&& data, std::integral_constant<int, 0>):data_(std::forward<U>(data)){}
    CurType data_;
    RecursiveUnion<Alternatives...> storage_;
};

template <typename T>
union RecursiveUnion<T> {
    template <typename U>
    RecursiveUnion(U&& data, std::integral_constant<int, 0>):data_(data){
    }
    T data_;
};



template <typename... Alternatives>
class Variant {
public:
    template <typename U>
    Variant(U&& data):storage_(std::forward<U>(data), std::integral_constant<int, helper<U, Alternatives...>::value>{}){}



    RecursiveUnion<Alternatives...>storage_;

};


int main() {

    Variant<int, long long>v(20);




    return 0;
}
