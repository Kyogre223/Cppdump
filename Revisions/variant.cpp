#include <bits/stdc++.h>
#include <string>
#include <string_view>
#include <cstddef>      // for std::size_t
#include <type_traits>  // for std::integral_constant
#include <utility>      // for std::forward


namespace Kai {
    template <typename...>
    union RecursiveUnion {};

    // for type count > 1
    template <typename T, typename... Others>
    union RecursiveUnion<T, Others...> {
        T item_;
        RecursiveUnion<Others...>storage_;
        template <typename U>
        RecursiveUnion(std::integral_constant<size_t, 0>, U&& data):item_(data){}

        template <typename U, size_t N>
        RecursiveUnion(std::integral_constant<size_t, N>, U&& data):
        storage_(std::integral_constant<size_t, N - 1>{}, std::forward<U>(data)){}

        ~RecursiveUnion() {

        }
        
    };

    // for only when 1 type is left.
    template<typename T>
    union RecursiveUnion<T> {
        template <typename U, size_t N>
        RecursiveUnion(std::integral_constant<size_t, N>, U&& data):item_(data){}
        T item_;

        ~RecursiveUnion(){}
    };
    template <typename... Types>
    class MyVariant {
        std::size_t index_ = 0;
        RecursiveUnion<Types...> storage_;

        template <typename... T>
        struct get_index{};

        template <typename T, typename U, typename... Us>
        struct get_index<T, U, Us...> {
            static constexpr std::size_t value =  1 + get_index<T, Us...>::value;
        };
        template <typename T, typename... Ts>
        struct get_index<T, T, Ts...> {
            static constexpr std::size_t value = 0;
        };

        public:
        template <typename T>
        MyVariant(T data):index_(get_index<T, Types...>::value), storage_(std::integral_constant<size_t, get_index<T, Types...>::value>{}, std::forward<T>(data)) {

        }

        std::size_t index() const {return index_;}

        ~MyVariant() {
            // destructor to allow for non-trivial types.
        }
    };




}



int main() {
    // it needs to have the ability to store multiple types.
    Kai::MyVariant<int, double, long long>var = 2.3;
    Kai::MyVariant<int, double, long long, std::string>var2 = std::string("KDZ!");
    return 0;
}
