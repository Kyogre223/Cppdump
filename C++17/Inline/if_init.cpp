//
// Created by Lin Kai on 28/10/24.
//

#include <iostream>
#include <vector>

// inline ?


struct A {
    static std::string name_;
};


// std::string A::name_{"kai"}; // link error if included by multiple cpp files

inline std::string A::name_{"Lin"}; // OK, use inline


// an alternative could be to just use templates


// generates better assembly than local static.
template <typename T = void>
struct B {
    static std::string name_;
};

template <>
std::string B<>::name_ = "Kai";



int main() {
    std::cout << B<>::name_ << '\n';
    std::cout << A::name_ << '\n';
    std::vector<int> V = {1, 2, 3, 4, 5};
    if (size_t sz = V.size(), test = 4; sz == 0) {
        std::cout << "Empty!\n";
        std::cout << test << '\n';
    } else {
        std::cout << "Nt!\n";
        std::cout << test << '\n';
    }


    return 0;
}
