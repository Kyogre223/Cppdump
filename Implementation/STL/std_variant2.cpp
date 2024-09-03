#include <iostream>
#include <cstring>
#include <string>
#include <functional>
#include <memory>
#include <variant>

// std::variant

template <typename...>
struct helper;

template <typename T, typename U, typename... Ts>
struct helper<T, U, Ts...> {
    constexpr static int value = 1 + helper<T, Ts...>::value;
};

template <typename T, typename... Ts>
struct helper<T, T, Ts...> {
    constexpr static int value = 0;
};

template <typename T>
struct helper<T> {
    constexpr static int value = -1e5;
};






template <typename T, typename... Alts>
union recursive_union {
    T data_;
    recursive_union<Alts...>recur_;
    template <int I, typename U>
    recursive_union(std::integral_constant<int, I>, U&& u):recur_(std::integral_constant<int, I - 1>(), u) {

    }

    template <typename U>
    recursive_union(std::integral_constant<int, 0>, U&& u):data_(std::forward<decltype(u)>(u)){

    }
    ~recursive_union() {

    }

    template <int I>
    auto& get() {
        if constexpr ( I == 0) {
            return data_;
        } else {
            return recur_.template get<I - 1>();
        }
    }

};

template <typename T>
union recursive_union<T> {
    T data_;
    template <typename U>
    recursive_union(std::integral_constant<int, 0>, U&& u):data_(u){}

    ~recursive_union() {

    }
    template <int I>
    auto& get() {
        return data_;
    }


};

template <typename... Alternatives>
struct MyVariant {
    recursive_union<Alternatives...> storage_;
    template <typename T>
    MyVariant(T data): storage_(std::integral_constant<int, helper<T, Alternatives...>::value>(), data){}
    ~MyVariant() {}

    template <typename T>
    auto& get() {
        return storage_.template get<helper<T, Alternatives...>::value>();
    }


};



int main() {
    std::variant<int, std::string, short, long>var(2);
    std::cout << std::get<0>(var) << '\n';
    std::cout << std::get<int>(var) << '\n';
    MyVariant<int, std::string, short>v2(std::string("Hello!"));
    std::cout << sizeof(v2) << '\n';
    std::cout << v2.get<std::string>() << '\n';

    // how to implement, the get functions ?





    return 0;
}
