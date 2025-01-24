#include <bits/stdc++.h>
#include <string>
#include <string_view>


template <typename T>
struct Rank {
    static constexpr size_t value = 0;
};

template <typename T>
struct Rank<T[]> {
    static constexpr size_t value = 1u + Rank<T>::value;
};

template <typename T, size_t N>
struct Rank<T[N]> {
    static constexpr size_t value = 1u + Rank<T>::value;
};



int main() {
    constexpr int mat[2][2] = {{1, 2}, {3, 4}};
    static_assert(Rank<decltype(mat)>::value == 2);
    return 0;
}
