//
// Created by Lin Kai on 21/10/24.
//

struct A {
    int x_;

    auto operator <=> (A const& other) const = default;
};
