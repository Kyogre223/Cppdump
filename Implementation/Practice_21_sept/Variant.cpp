//
// Created by Lin Kai on 21/9/24.
//


#include <iostream>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <thread>
#include <iostream>
#include <memory>
#include <algorithm>

template <typename...>
struct helper;

template <typename T, typename... Ts>
struct helper<T, T, Ts...> {
    constexpr static int value = 0;
};

template <typename U, typename T, typename... Ts>
struct helper<U, T, Ts...> {
    constexpr static int value = 1 + helper<U, Ts...>::value;
};

template <typename T>
struct helper <T> {
    constexpr static int value = -1e5;
};



struct A{
    A() {
        std::cout << "ctor\n";
    }
    ~A() {
        std::cout << "dtor\n";
    }
};


// implement variant
template <typename T, typename... Ts>
union Recursive_Union {
    T data_;
    Recursive_Union<Ts...> storage_;
    template <typename U, int I>
    Recursive_Union(U&& data, std::integral_constant<int, I>): storage_(std::forward<U>(data), std::integral_constant<int, I - 1>{}) {

    }
    template <typename U>
    Recursive_Union(U&& data, std::integral_constant<int, 0>):data_{std::forward<U>(data)}{}

    ~Recursive_Union(){}

    template <int I>
    auto& get() {
        if constexpr (I == 0) {
            return data_;
        } else {
            return storage_.template get<I-1>();
        }
    }

};


template <typename T>
union Recursive_Union<T> {
    T data_;
    template <typename U, int I>
    Recursive_Union(U&& data, std::integral_constant<int, I>)
            : data_{std::forward<U>(data)}
    {}

    ~Recursive_Union(){}
    template <int I>
    auto& get() {
        return data_;
    }
};

template <typename... Ts>
class MyVariant {

    Recursive_Union<Ts...> storage_;
    int index_;
public:
    template <typename T>
    MyVariant(T&& data_):storage_(std::forward<T>(data_), std::integral_constant<int, helper<T, Ts...>::value>{}) {
        index_ = helper<T, Ts...>::value;
        static_assert(helper<T, Ts...>::value >= 0, "No type found within variant");
    }

    ~MyVariant() {}

    int index() const {return index_;}
};

int main() {
    MyVariant<double, int, long long>v(1);
    std::cout << "index: " << v.index() << '\n';
    std::cout << sizeof(Recursive_Union<double, int, long long>) << '\n';
    MyVariant<double, int, long long>v2(1LL);
    std::cout << v2.index() << '\n';
    MyVariant<double, int, long long, std::string>v3(std::string("Hello world!\n"));
    MyVariant<double, int, long long, std::string, A>v4(A{});



    return 0;
}