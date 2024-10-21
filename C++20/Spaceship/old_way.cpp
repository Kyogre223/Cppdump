//
// Created by Lin Kai on 21/10/24.
//
#include <iostream>
#include <vector>
#include <algorithm>


struct A {
    int x_;

    friend constexpr bool operator < (A const& lhs, A const& rhs) noexcept {
        return lhs.x_ < rhs.x_;
    }
};


int main() {
    std::vector<A> V;
    V.emplace_back(5);
    V.emplace_back(10);
    V.emplace_back(2);

    std::sort(V.begin(), V.end());
    for (auto& v : V) {
        std::cout << v.x_ << '\n';
    }


    return 0;
}
